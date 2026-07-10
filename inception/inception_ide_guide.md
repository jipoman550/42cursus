# Antigravity IDE를 활용한 Inception 프로젝트 개발 및 검증 가이드

본 문서는 Antigravity IDE의 정적 분석, 코드 생성 및 탐색 기능을 활용하여 42 Inception 프로젝트의 모든 필수 제약 조건을 준수하며 인프라를 안전하게 빌드하고 검증하는 단계별 교육용 가이드라인을 제공합니다.

---

## 1단계: 프로젝트 구조 설계 및 IDE 컨텍스트 인덱싱

프로젝트 수행 전, AI가 과제 PDF 및 프로젝트 구조를 오독하지 않도록 작업 공간을 설정하고 인덱싱하는 단계입니다.

### 1.1 표준 디렉토리 구조 설정
Inception 과제는 명확하고 구조화된 디렉토리 레이아웃을 요구합니다. 작업 공간 루트에 아래 구조를 구성합니다.

```text
/home/sisung/workspace/42cursus/inception
├── Makefile
├── inception_ide_guide.md  (본 가이드)
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf
        │   └── tools/
        │       └── mariadb_setup.sh
        ├── nginx/
        │   ├── Dockerfile
        │   └── conf/
        │       └── nginx.conf
        └── wordpress/
            ├── Dockerfile
            ├── conf/
            │   └── www.conf
            └── tools/
                └── wordpress_setup.sh
```

### 1.2 과제 제약 조건(en.subject_inception.pdf) 인덱싱 및 검증
Antigravity IDE가 서브젝트 파일인 [en.subject_inception.pdf](file:///home/sisung/workspace/42cursus/inception/en.subject_inception.pdf)의 제약 조건을 완벽하게 이해하고 있는지 확인하기 위해, IDE 콘솔 또는 에이전트 프롬프트 창에 다음 명령어를 입력하여 파일 내용을 분석하도록 요청합니다.

*   **IDE 컨텍스트 확인 프롬프트:**
    ```text
    [en.subject_inception.pdf](file:///home/sisung/workspace/42cursus/inception/en.subject_inception.pdf) 파일을 분석하여 필수 파트(Mandatory Part)의 NGINX TLS 사양, 볼륨 마운트 경로, 허용되지 않는 Docker 구성 요소를 요약해 주십시오.
    ```

---

## 2단계: PID 1 원칙을 준수하는 Dockerfile 프로토타입 작성 및 검증

컨테이너가 비정상적으로 종료되는 것을 방지하기 위해 `tail -f`, `sleep infinity` 같은 편법 루프를 엔트리포인트 스크립트에 심는 것은 금지됩니다. 각 서비스 데몬을 포그라운드(Foreground)에서 실행하여 PID 1로 동작하도록 제어해야 합니다.

### 2.1 NGINX Dockerfile 및 설정
NGINX는 포트 443과 TLSv1.2/TLSv1.3 프로토콜만 허용해야 합니다. Base Image는 Debian Bullseye(penultimate stable version)를 사용합니다.

#### Dockerfile 생성 프롬프트 예시
```text
Debian Bullseye를 베이스 이미지로 사용하여 NGINX 컨테이너용 Dockerfile을 생성하십시오.
- 패키지 업데이트 및 nginx, openssl 설치
- 자체 서명 SSL 인증서 생성 (TLSv1.2 이상 통신용)
- 포그라운드 모드로 NGINX 실행 (nginx -g 'daemon off;'를 CMD로 지정)
```

#### NGINX 설정 파일 검증 ([nginx.conf](file:///home/sisung/workspace/42cursus/inception/srcs/requirements/nginx/conf/nginx.conf))
```nginx
server {
    listen 443 ssl;
    listen [::]:443 ssl;

    server_name login.42.fr;

    ssl_certificate /etc/nginx/ssl/inception.crt;
    ssl_certificate_key /etc/nginx/ssl/inception.key;

    # 필수 요구 조건: TLSv1.2 또는 TLSv1.3만 허용
    ssl_protocols TLSv1.2 TLSv1.3;

    root /var/www/wordpress;
    index index.php index.html index.htm;

    location / {
        try_files $uri $uri/ =404;
    }

    location ~ \.php$ {
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
        fastcgi_pass wordpress:9000;
        fastcgi_index index.php;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_param PATH_INFO $fastcgi_path_info;
    }
}
```

### 2.2 MariaDB Dockerfile 및 엔트리포인트
MariaDB 데몬이 백그라운드로 실행된 후 종료되지 않도록 `exec mysqld` 혹은 `exec mysqld_safe`를 통해 PID 1을 유지하도록 작성합니다.

#### MariaDB Dockerfile 프로토타입
```dockerfile
FROM debian:bullseye

RUN apt-get update -y && \
    apt-get install -y mariadb-server mariadb-client && \
    rm -rf /var/lib/apt/lists/*

# 외부 연결 허용을 위한 설정 파일 복사
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

COPY tools/mariadb_setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/mariadb_setup.sh

EXPOSE 3306

ENTRYPOINT ["mariadb_setup.sh"]
```

#### [mariadb_setup.sh](file:///home/sisung/workspace/42cursus/inception/srcs/requirements/mariadb/tools/mariadb_setup.sh) 내 PID 1 실행 구조
```bash
#!/bin/sh
set -e

# MariaDB 초기화
if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# 임시 데몬 실행 후 DB/유저 생성 및 권한 설정
# (생략: .env 파일로부터 전달받은 환경 변수 활용)

# 최종 데몬을 exec 명령어로 포그라운드 실행하여 PID 1로 전환
exec mysqld --user=mysql --console
```

### 2.3 WordPress + php-fpm Dockerfile 및 설정
php-fpm은 기본적으로 백그라운드 데몬으로 실행되므로, 포그라운드로 실행하기 위해 `-F` 옵션을 지정해야 합니다.

#### [www.conf](file:///home/sisung/workspace/42cursus/inception/srcs/requirements/wordpress/conf/www.conf) 설정 검증
```ini
; 포트 9000번에서 외부 컨테이너(NGINX)의 요청을 대기하도록 설정
listen = 9000
```

#### WordPress Dockerfile CMD 구조
```dockerfile
# php-fpm7.4 포그라운드 실행 제어
CMD ["/usr/sbin/php-fpm7.4", "-F"]
```

---

## 3단계: docker-compose.yml 및 커스텀 네트워크 정적 검사

`docker-compose.yml` 파일 작성 시 아래 금지 조항을 위반했는지 IDE의 검색 및 린팅 기능을 통해 검출합니다.

### 3.1 필수 검증 항목
1.  `network_mode: host` 사용 여부 금지
2.  `links:` 옵션 사용 금지
3.  바인드 마운트 사용 금지 (Named Volume 및 local driver_opts 활용)

### 3.2 [docker-compose.yml](file:///home/sisung/workspace/42cursus/inception/srcs/docker-compose.yml) 구조 및 정적 검사 예시
```yaml
version: '3.8'

services:
  nginx:
    build:
      context: ./requirements/nginx
      dockerfile: Dockerfile
    container_name: nginx
    ports:
      - "443:443"
    networks:
      - inception-network
    volumes:
      - wordpress-data:/var/www/wordpress
    depends_on:
      - wordpress
    restart: always

  wordpress:
    build:
      context: ./requirements/wordpress
      dockerfile: Dockerfile
    container_name: wordpress
    networks:
      - inception-network
    volumes:
      - wordpress-data:/var/www/wordpress
    env_file:
      - .env
    depends_on:
      - mariadb
    restart: always

  mariadb:
    build:
      context: ./requirements/mariadb
      dockerfile: Dockerfile
    container_name: mariadb
    networks:
      - inception-network
    volumes:
      - mariadb-data:/var/lib/mysql
    env_file:
      - .env
    restart: always

networks:
  inception-network:
    driver: bridge

volumes:
  wordpress-data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/sisung/data/wordpress
  mariadb-data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/sisung/data/mariadb
```

*   **IDE를 통한 검증 프롬프트:**
    ```text
    [docker-compose.yml](file:///home/sisung/workspace/42cursus/inception/srcs/docker-compose.yml) 파일에서 'links' 키워드나 'network_mode' 키워드가 사용되었는지 정적 검색을 수행하고, 볼륨 바인딩 설정이 '/home/로그인/data' 형태의 로컬 네임드 볼륨으로 지정되었는지 검증해 주십시오.
    ```

---

## 4단계: 민감 정보 하드코딩 교차 검증 (보안 필터링)

비밀번호, DB 사용자 ID 등의 민감 정보가 Git에 커밋되거나 소스코드 내부에 하드코딩되는 것을 검사하는 프로세스입니다.

### 4.1 `.env` 템플릿 정의 및 `.gitignore` 등록
`srcs/.env` 파일에는 다음 변수들이 정의되어 있어야 합니다.

```env
MYSQL_ROOT_PASSWORD=root_password_here
MYSQL_DATABASE=inception_db
MYSQL_USER=wp_user
MYSQL_PASSWORD=wp_password_here
WP_ADMIN_USER=wp_admin
WP_ADMIN_PASSWORD=wp_admin_password
WP_USER=wp_regular_user
WP_USER_PASSWORD=wp_regular_password
```
*(주의: WordPress 관리자 이름에 `admin` 또는 `administrator` 키워드를 포함해서는 안 됩니다.)*

### 4.2 IDE 검색 기능을 활용한 보안 교차 검증
하드코딩된 비밀번호가 존재하지 않는지 프로젝트 전체에서 정적 분석 도구를 사용하여 검출합니다.

*   **IDE 탐색 명령어:**
    프로젝트 내부 파일에서 환경변수가 아닌 실제 비밀번호를 직접 대입한 구문(예: `password=`, `PASS=`)이 발견되는지 `grep_search`를 통해 체크합니다.
    ```bash
    # 비밀번호 하드코딩 흔적 정적 탐색 명령어 예시
    grep -rnw './srcs' -e 'MYSQL_PASSWORD' -e 'MYSQL_ROOT_PASSWORD'
    ```

---

## 5단계: Makefile 빌드 및 PID 1 데몬 검증 절차

호스트 OS(Linux) 환경에서 인프라를 빌드하고 컨테이너 내부 프로세스가 PID 1 규칙을 만족하는지 검사하는 최종 단계입니다.

### 5.1 [Makefile](file:///home/sisung/workspace/42cursus/inception/Makefile) 템플릿
```makefile
NAME = inception

SRCS_DIR = ./srcs
DOCKER_COMPOSE = docker-compose -f $(SRCS_DIR)/docker-compose.yml

all: build up

build:
	mkdir -p /home/sisung/data/wordpress
	mkdir -p /home/sisung/data/mariadb
	$(DOCKER_COMPOSE) build

up:
	$(DOCKER_COMPOSE) up -d

down:
	$(DOCKER_COMPOSE) down

clean: down
	docker system prune -a -f

fclean: clean
	sudo rm -rf /home/sisung/data

re: fclean all

.PHONY: all build up down clean fclean re
```

### 5.2 컨테이너 구동 상태 및 PID 1 확인 명령어
컨테이너 빌드가 완료된 후, 호스트 터미널에서 다음 명령어를 실행하여 각 데몬이 백그라운드 무한 루프 래퍼 없이 올바르게 PID 1로 실행되고 있는지 최종 확인합니다.

```bash
# 1. 실행 중인 컨테이너 리스트 확인
docker ps

# 2. MariaDB 컨테이너 내부 PID 1 동작 프로세스 확인
docker exec -it mariadb ps -ef

# 3. NGINX 컨테이너 내부 PID 1 동작 프로세스 확인
docker exec -it nginx ps -ef

# 4. WordPress 컨테이너 내부 PID 1 동작 프로세스 확인
docker exec -it wordpress ps -ef
```

*   **올바른 결과 예시 (NGINX의 경우):**
    ```text
    UID        PID  PPID  C STIME TTY          TIME CMD
    root         1     0  0 09:00 ?        00:00:00 nginx: master process nginx -g daemon off;
    www-data     6     1  0 09:00 ?        00:00:00 nginx: worker process
    ```
    *(PID 1이 `nginx` 마스터 프로세스여야 하며, `tail -f`나 `bash` 스크립트가 PID 1을 점유한 채 대기하는 형태가 아니어야 합니다.)*

---

## 6단계: 보너스 인프라 확장 및 격리 검증

본 단계는 필수 인프라 구성 완료 후 성능 향상(Redis), 관리 도구(Adminer, Portainer), 편의 기능(FTP), 정적 페이지 호스팅 등 5가지 보너스 서비스를 격리된 독립 컨테이너 환경으로 가동하는 과정입니다.

### 6.1 보너스 추가 구조 설정
`srcs/requirements/bonus/` 하위에 각 보너스 서비스별 Dockerfile과 설정들을 배치합니다.
```text
srcs/requirements/bonus/
├── adminer/
│   └── Dockerfile
├── ftp/
│   ├── Dockerfile
│   ├── conf/
│   │   └── vsftpd.conf
│   └── tools/
│       └── ftp_setup.sh
├── redis/
│   └── Dockerfile
└── static/
    ├── Dockerfile
    └── conf/
        └── nginx.conf
```

### 6.2 Redis 및 FTP 컨테이너 연동
Redis 캐시 서버와 FTP 서버를 구축하여 WordPress와 물리 Named Volume(`wordpress-data`)을 공유 마운트하고 통신하도록 설정합니다.

*   **Redis 설정 핵심**: `redis.conf`에서 `protected-mode no` 및 `bind 0.0.0.0`으로 지정하여 wordpress 컨테이너의 캐시 요청을 내부망에서 수락합니다.
*   **FTP 설정 핵심**: Passive 모드 포트(`30000-30009`)를 명시적으로 개방하고, `chroot_local_user=YES` 및 `allow_writeable_chroot=YES`를 설정해 사용자가 WordPress 루트 디렉토리를 벗어나지 못하게 제한합니다.

### 6.3 Adminer 및 정적 사이트 웹 라우팅 설정
NGINX 컨테이너의 설정 파일(`nginx.conf`)을 업데이트하여 포트 443(TLSv1.2/1.3)을 통해 들어오는 `/adminer` 및 `/static` 요청을 각각의 보너스 컨테이너로 리버스 프록싱합니다.

*   **Adminer 라우팅 예시 (nginx.conf)**:
    ```nginx
    location /adminer {
        root /var/www/adminer;
        index index.php;
        try_files $uri $uri/ /adminer/index.php$is_args$args;

        location ~ \.php$ {
            include fastcgi_params;
            fastcgi_pass adminer:9000;
            fastcgi_param SCRIPT_FILENAME /var/www/adminer/index.php;
        }
    }
    ```

*   **IDE를 통한 보너스 서비스 검증 프롬프트:**
    ```text
    [docker-compose.yml](file:///home/sisung/workspace/42cursus/inception/srcs/docker-compose.yml) 파일에 추가된 보너스 서비스들이 동일한 사용자 정의 브리지 네트워크에 묶여 있는지 확인하고, FTP 포트 외의 내부 서비스들(Redis, Adminer)의 포트가 외부 호스트에 다이렉트로 노출되지 않고 격리되었는지 검증해 주십시오.
    ```


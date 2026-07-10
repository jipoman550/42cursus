# Step 2: PID 1 원칙 및 Dockerfile 설계 (PID 1 Principle & Dockerfile Design)

## 1. 해당 단계의 개요 및 마일스톤 계획
본 단계는 Inception 인프라를 구성하는 각 서비스(NGINX, MariaDB, WordPress)의 개별 Dockerfile과 초기화 스크립트(Entrypoint)를 작성하는 단계입니다. 컨테이너 환경의 핵심 구동 규칙인 PID 1 원칙을 정확하게 적용하여 불필요한 좀비 프로세스의 누적을 막고 안전하게 프로세스가 라이프사이클을 유지하도록 구현합니다.

### 마일스톤 계획
1. **NGINX Dockerfile 작성**: Debian Bullseye 베이스를 기반으로 하며 TLSv1.2 및 TLSv1.3만을 사용하도록 OpenSSL 인증서를 설정하고 포그라운드 실행하도록 설계.
2. **MariaDB Dockerfile 및 Entrypoint 설계**: 안전한 DB 초기화 루틴을 구성하고 `exec`를 통하여 백그라운드 전환 없이 포그라운드 실행.
3. **WordPress Dockerfile 및 Entrypoint 설계**: wp-cli를 사용하여 WP 사이트를 완전 초기화하고, php-fpm을 포그라운드 모드로 가동.
4. **PID 1 무결성 진단**: 초기화 스크립트가 프로세스를 점유하거나 쉘 환경을 유지하는 문제를 예방하기 위한 검증 구조 수립.

---

## 2. 필수 핵심 개념 정리

### 커널 PID 1 (Init 프로세스)의 역할과 좀비 프로세스 회수 메커니즘
* **PID 1의 책임**: 유닉스 계열 운영체제에서 PID 1은 모든 프로세스의 부모 프로세스인 `init` 프로세스입니다. 컨테이너 런타임 환경에서는 `Dockerfile`의 `ENTRYPOINT` 또는 `CMD`에 기술된 명령어가 PID 1을 할당받습니다.
* **좀비 프로세스(Zombie Process) 회수**: 자식 프로세스가 종료되었으나 부모 프로세스가 해당 리턴 코드를 수집(Reaping)하지 않을 경우 리소스 테이블을 점유하는 좀비 상태로 남습니다. 일반 OS에서는 PID 1이 이 고아 프로세스들의 소유권을 이전받아 회수(`wait()`/`waitpid()`)하지만, 올바르게 설계되지 않은 컨테이너 진입 프로세스(예: 단순 쉘 스크립트)는 시그널 처리 및 좀비 프로세스 소집 기능을 정상적으로 수행하지 못합니다.
* **시그널 포워딩**: Docker가 컨테이너를 중지할 때(SIGTERM 등) PID 1에 시그널이 전송됩니다. PID 1이 시그널 핸들러를 처리하지 못하면 컨테이너는 10초 대기 후 SIGKILL에 의해 강제 종료됩니다.

### Hacky Patches가 컨테이너 오작동을 일으키는 이유
* **Hacky Patches의 정의**: `tail -f /dev/null`, `sleep infinity`, `while true; do sleep 1; done` 등의 임시방편 루프.
* **오작동 원리**:
  1. 데몬 프로세스(예: `service nginx start`)가 구동된 후 스크립트 종료를 막기 위해 루프를 걸 경우, 컨테이너 프로세스 트리에서 `tail` 또는 `sleep`이 PID 1을 점유하게 됩니다.
  2. 실제 주요 서비스 데몬이 비정상 종료(Crash)하더라도 PID 1인 `tail` 또는 `sleep` 프로세스는 활성 상태를 유지하므로, Docker 엔진은 컨테이너가 정상 구동 중인 것으로 오판하여 복구 메커니즘(`restart: always`)을 트리거하지 않습니다.
  3. 시그널(SIGTERM) 수신 시 `tail`이 이를 무시하여 컨테이너가 정상 종료되지 못하고 강제 종료(Graceful shutdown 실패)를 초래합니다.

### FastCGI (php-fpm)와 웹서버 (NGINX)의 통신 구조
* **동작 원리**: NGINX는 자체적으로 PHP 파일의 해석(Execution) 기능이 없습니다. 따라서 클라이언트가 PHP 스크립트를 요청하면 NGINX는 FastCGI 프로토콜을 사용해 네트워크 포트(9000번) 혹은 Unix Domain Socket을 통해 php-fpm 프로세스 엔진으로 실행 요청을 위임합니다.
* **인프라 구조**: 본 과제 규정에 따라 NGINX와 WordPress(php-fpm)는 서로 다른 격리된 컨테이너 내부에서 실행되므로, 루프백 주소(`127.0.0.1`)가 아닌 Docker Internal Network 상의 서비스 명인 `wordpress:9000`을 통해 TCP 포트로 직접 통신합니다.

---

## 3. 상세 할 일 목록 (To-Do List)

- [ ] **NGINX 설정 및 Dockerfile 생성**
  * Debian Bullseye 베이스 지정.
  * SSL 인증서 보관 경로 생성 및 OpenSSL을 통한 자체 서명 인증서(TLSv1.2 이상) 발행.
  * 포그라운드 실행을 보장하는 CMD 명령 구성 (`nginx -g 'daemon off;'`).

- [ ] **MariaDB 설정 및 Entrypoint 생성**
  * `/var/lib/mysql` 디렉토리 소유권 및 접근 권한 구성.
  * 외부 액세스 허용을 위해 `50-server.cnf` 내의 `bind-address` 속성을 `0.0.0.0`으로 재할당.
  * 초기화 동작 완료 후, `exec mysqld --user=mysql --console`을 실행하여 쉘 래퍼를 벗겨내고 `mysqld`에 PID 1 양도.

- [ ] **WordPress (php-fpm) 설정 및 Entrypoint 생성**
  * `wp-cli.phar` 패키지 다운로드 및 실행 권한 부여하여 `/usr/local/bin/wp`로 구성.
  * `www.conf`를 수정하여 `listen = 9000` 설정 변경.
  * `/var/www/wordpress` 하위에 WordPress 소스 코드 다운로드 및 압축 해제.
  * 초기화 동작 후 `exec php-fpm7.4 -F` 명령어를 반영하여 포그라운드 실행 및 PID 1 양도.

---

## 4. 정확한 설정 파일 예시 및 코드 스니펫

### 1) NGINX Dockerfile (`srcs/requirements/nginx/Dockerfile`)
```dockerfile
FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

# SSL 디렉토리 생성 및 자체 서명 인증서 생성
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/inception.key \
    -out /etc/nginx/ssl/inception.crt \
    -subj "/C=KR/ST=Seoul/L=Gaepo/O=42Seoul/OU=Member/CN=sisung.42.fr"

# NGINX 설정 복사
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

# 포그라운드 실행을 통해 PID 1 획득
ENTRYPOINT ["nginx", "-g", "daemon off;"]
```

### 2) NGINX 서버 설정 (`srcs/requirements/nginx/conf/nginx.conf`)
```nginx
server {
    listen 443 ssl;
    listen [::]:443 ssl;

    server_name sisung.42.fr;

    ssl_certificate /etc/nginx/ssl/inception.crt;
    ssl_certificate_key /etc/nginx/ssl/inception.key;

    # TLSv1.2 및 TLSv1.3만 명시적으로 허용
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_prefer_server_ciphers on;

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

### 3) MariaDB Dockerfile (`srcs/requirements/mariadb/Dockerfile`)
```dockerfile
FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    mariadb-server \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/mariadb_setup.sh /usr/local/bin/mariadb_setup.sh

RUN chmod +x /usr/local/bin/mariadb_setup.sh && \
    mkdir -p /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld /var/lib/mysql

EXPOSE 3306

ENTRYPOINT ["/usr/local/bin/mariadb_setup.sh"]
```

### 4) MariaDB 초기화 쉘 스크립트 (`srcs/requirements/mariadb/tools/mariadb_setup.sh`)
```bash
#!/bin/sh
set -e

# MariaDB 데이터베이스 디렉토리가 비어있을 시 초기 스키마 설치
if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# 임시 안전 모드로 MariaDB 백그라운드 실행 (초기 사용자 설정용)
mysqld_safe --datadir=/var/lib/mysql &
PID=$!

# DB 소켓 생성 대기
until mysqladmin ping --silent; do
    sleep 1
done

# root 비밀번호 및 신규 사용자 설정 SQL 실행
mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';"
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" -e "FLUSH PRIVILEGES;"

# 임시 백그라운드 서버 종료
mysqladmin -u root -p"${MYSQL_ROOT_PASSWORD}" shutdown
wait $PID

# exec 명령어로 실제 서비스 데몬을 실행하여 PID 1 획득 (Hacky Loops 차단)
exec mysqld --user=mysql --console
```

### 5) WordPress Dockerfile (`srcs/requirements/wordpress/Dockerfile`)
```dockerfile
FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php7.4-fpm \
    php7.4-mysql \
    mariadb-client \
    curl \
    && rm -rf /var/lib/apt/lists/*

# PHP-FPM 실행을 위한 런타임 디렉토리 생성
RUN mkdir -p /run/php

# WP-CLI 도구 설치
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf
COPY tools/wordpress_setup.sh /usr/local/bin/wordpress_setup.sh
RUN chmod +x /usr/local/bin/wordpress_setup.sh

WORKDIR /var/www/wordpress

ENTRYPOINT ["/usr/local/bin/wordpress_setup.sh"]
```

### 6) WordPress 초기화 쉘 스크립트 (`srcs/requirements/wordpress/tools/wordpress_setup.sh`)
```bash
#!/bin/sh
set -e

# MariaDB 활성화 대기 루프
until mysqladmin ping -h"mariadb" --silent; do
    sleep 2
done

# WordPress 설치 파일 다운로드 및 구성
if [ ! -f "wp-config.php" ]; then
    wp core download --allow-root
    wp config create --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost=mariadb \
        --path="/var/www/wordpress"

    wp core install --allow-root \
        --url="${DOMAIN_NAME}" \
        --title="Inception Site" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_USER}@student.42.fr" \
        --path="/var/www/wordpress"

    wp user create "${WP_USER}" "${WP_USER}@student.42.fr" \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}" \
        --allow-root \
        --path="/var/www/wordpress"
fi

# php-fpm 프로세스 소유권을 www-data에 명시적으로 전달
chown -R www-data:www-data /var/www/wordpress

# exec 명령어로 php-fpm을 포그라운드 모드(-F)로 가동하여 PID 1 획득
exec /usr/sbin/php-fpm7.4 -F
```

---

## 5. 전용 검증 프롬프트 세트

### [검증 프롬프트 1 - Dockerfile 정적 린팅 및 PID 1 확인]
> Antigravity, NGINX, MariaDB, WordPress의 `Dockerfile`들을 열어 베이스 이미지가 `debian:bullseye`로 바르게 선언되었는지 확인하고, 각각의 엔트리포인트 및 CMD에서 쉘 감싸기 없이 실행되는 exec 포맷(`exec` 구문 혹은 `CMD [...]` JSON 배열 선언 형태)으로 작성되었는지 정적 분석해줘.

### [검증 프롬프트 2 - 엔트리포인트 내 Hacky Patches 검출]
> Antigravity, 각 서비스의 툴즈 내부에 정의된 초기화 쉘 스크립트(`mariadb_setup.sh`, `wordpress_setup.sh`)에서 무한 대기 목적의 `tail -f`, `sleep infinity`, `while true`와 같은 하드코딩된 핵키 루프가 사용되었는지 전체 파일 내용의 정적 패턴을 분석해줘.

# Step 6: 보너스 인프라 확장 (Bonus Part Infrastructure Expansion)

## 1. 해당 단계의 개요 및 마일스톤 계획
본 단계는 Inception의 Mandatory 인프라(NGINX, MariaDB, WordPress)가 완벽하게 가동된 후, 인프라의 성능 개선, 관리 편의성, 그리고 부가 기능 제공을 위해 5가지 보너스 서비스를 통합하는 단계입니다. 각 보너스 서비스는 독립된 전용 Dockerfile과 볼륨(필요시)을 갖춘 격리된 컨테이너로 배포되어야 합니다.

### 마일스톤 계획
1. **Redis Cache 설정**: WordPress의 DB 쿼리 부하 분산을 위한 Redis 캐시 메모리 레이어 구축.
2. **FTP Server 구축**: WordPress 웹 루트 디렉토리(/var/www/wordpress) 볼륨을 지시하는 FTP 서버 구성.
3. **Adminer 구축**: 단일 PHP 스크립트 기반의 가벼운 웹 데이터베이스 관리 도구 배치.
4. **정적 웹사이트(Static Website) 구축**: PHP를 배제한 순수 HTML/CSS/JS 기반 쇼케이스 페이지 호스팅.
5. **추가 커스텀 서비스 구성**: 인프라 관리 향상을 위한 Portainer 가동 및 보안 격리 유지.
6. **포트 개방 및 라우팅 제어**: 보너스 동작을 위한 추가 외부 포트 맵 매핑 및 NGINX 리버스 프록시 연계.

---

## 2. 필수 핵심 개념 정리

### Redis의 메모리 내 데이터 캐싱 및 WordPress 연동 원리
* **인-메모리 캐싱**: Redis(Remote Dictionary Server)는 데이터를 디스크가 아닌 메인 메모리(RAM)에 Key-Value 구조로 저장하는 데이터 저장소입니다. 읽기/쓰기 속도가 극도로 빠릅니다.
* **WordPress 쿼리 캐시(Object Cache)**: WordPress는 데이터 요청 시 매번 MariaDB에 SQL 쿼리를 질의하여 페이지를 렌더링하므로 병목이 발생합니다. Redis Object Cache 플러그인을 WordPress에 탑재하면, 동일한 쿼리 결과나 빈번히 로드되는 구성 데이터를 Redis 메모리에 임시 보관하여 DB에 도달하기 전에 초고속으로 리턴합니다.

### FTP 프로토콜(Active/Passive 모드) 및 볼륨 공유 통신 구조
* **FTP 전송 메커니즘**: FTP(File Transfer Protocol)는 명령용 제어 채널(포트 21)과 데이터 전송용 데이터 채널을 독립적으로 사용합니다. 방화벽과 NAT 환경이 표준이 된 가상 머신 인프라에서는 클라이언트가 제안한 임의의 포트 범위로 서버가 대기하는 **Passive Mode** 설정이 필수적입니다.
* **데이터 공유 볼륨 구조**: FTP 컨테이너는 WordPress 컨테이너의 소스 코드가 적재된 Named Volume(`wordpress-data`)을 동일하게 공유 마운트합니다. 사용자가 FTP를 통해 파일을 전송하거나 수정하면, WordPress 실행 엔진에 즉각 반영되는 공유 데이터 격리 구조를 가집니다.

### PHP 제외 정적 웹사이트(Static HTML/JS) 호스팅 원리
* **동적 vs 정적 리소스**: WordPress와 달리 정적 HTML/CSS/Javascript는 서버 사이드 계산이나 런타임(PHP 등) 해석이 필요하지 않고, 클라이언트(브라우저)에서 100% 렌더링됩니다.
* **호스팅 및 포트 포워딩**: NGINX 또는 Alpine 기반의 가벼운 웹서버를 이용하여 정적 리소스를 제공합니다. NGINX에서 리버스 프록시 또는 가상 호스팅을 설정하여 특정 도메인 주소(예: `sisung.42.fr/bonus` 혹은 추가 포트)를 통해 액세스하도록 제어합니다.

### Adminer의 아키텍처 및 MariaDB 데이터베이스 브리지 통신
* **Adminer의 경량 아키텍처**: 무겁고 복잡한 phpMyAdmin과 달리, Adminer는 하나의 완성된 PHP 파일(`adminer.php`)로만 동작합니다.
* **DB 브리지**: Adminer 컨테이너는 동일한 Docker Bridge Network인 `inception-network`에 가입되어, DNS 해석을 통해 `mariadb:3306` 포트로 쿼리 질의를 안전하게 수행할 수 있습니다.

### 추가 커스텀 서비스(Portainer) 설정 정당성
* **Portainer의 역할**: Portainer는 Docker 데몬 API 소켓(`docker.sock`)을 통신 수단으로 삼아 구동 중인 컨테이너 상태, 이미지 레이어, 가상 네트워크 및 볼륨 바인딩 정보를 시각화해 주는 웹 기반 GUI 관리 콘솔입니다.
* **보안 격리 정책**: docker.sock을 바인딩하여 호스트의 모든 컨테이너 권한을 통제하므로, 절대 외부 포트에 노출되지 않고 내부 로컬망 또는 NGINX 리프록시를 통해서만 보안 인가를 얻도록 제어해야 합니다.

---

## 3. 상세 할 일 목록 (To-Do List)

- [ ] **Redis 컨테이너 설정 및 가동**
  * `redis:alpine` 또는 Debian 기반 Dockerfile 빌드.
  * `redis.conf` 설정 파일 내 `protected-mode no` 및 `bind 0.0.0.0` 변경.
  * WordPress 내 Redis Object Cache 플러그인 설정 스크립트 작성.

- [ ] **FTP(vsftpd) 서버 구축**
  * `vsftpd` 패키지를 적재한 독립 Dockerfile 설계.
  * vsftpd.conf의 로컬 루트를 `/var/www/wordpress`로 고정하고 익명 업로드 차단.
  * Passive 포트 대역 설정 (`pasv_min_port=30000`, `pasv_max_port=30009` 등) 및 compose 파일 포트 노출.

- [ ] **Adminer 단일 페이지 가동**
  * php 기반 컨테이너 내 `/var/www/adminer` 하위에 최신 `adminer.php` 설치.
  * 포트 9000번 대기 혹은 내부용 NGINX와 연동.

- [ ] **정적 웹사이트 구성**
  * 정적 HTML/CSS 자산 생성 및 NGINX 경량 웹서버 설정.
  * `srcs/requirements/bonus/static` 폴더 스캐폴딩.

- [ ] **Portainer 서비스 연동**
  * Portainer Dockerfile 작성 및 `/var/run/docker.sock` 바인드 마운트 구성.

- [ ] **docker-compose.yml 리빌드 및 NGINX 프록시 업데이트**
  * NGINX 설정을 변경하여 Adminer 및 정적 사이트를 라우팅.

---

## 4. 정확한 설정 파일 예시 및 코드 스니펫

### 1) Redis Dockerfile (`srcs/requirements/bonus/redis/Dockerfile`)
```dockerfile
FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    redis-server \
    && rm -rf /var/lib/apt/lists/*

# Redis 메모리 보호 해제 및 포트 오픈
RUN sed -i "s|bind 127.0.0.1|bind 0.0.0.0|g" /etc/redis/redis.conf && \
    sed -i "s|protected-mode yes|protected-mode no|g" /etc/redis/redis.conf && \
    sed -i "s|daemonize yes|daemonize no|g" /etc/redis/redis.conf

EXPOSE 6379

ENTRYPOINT ["redis-server", "/etc/redis/redis.conf"]
```

### 2) FTP 서버 Dockerfile (`srcs/requirements/bonus/ftp/Dockerfile`)
```dockerfile
FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    vsftpd \
    && rm -rf /var/lib/apt/lists/*

# 설정 복사 및 계정 생성 엔트리포인트 실행
COPY conf/vsftpd.conf /etc/vsftpd.conf
COPY tools/ftp_setup.sh /usr/local/bin/ftp_setup.sh
RUN chmod +x /usr/local/bin/ftp_setup.sh

EXPOSE 21 30000-30009

ENTRYPOINT ["/usr/local/bin/ftp_setup.sh"]
```

### 3) FTP 초기화 스크립트 (`srcs/requirements/bonus/ftp/tools/ftp_setup.sh`)
```bash
#!/bin/sh
set -e

# FTP 전용 사용자 추가 및 패스워드 대입
if [ ! -d "/var/run/vsftpd/empty" ]; then
    mkdir -p /var/run/vsftpd/empty
fi

if ! id "${FTP_USER}" >/dev/null 2>&1; then
    useradd -m -d /var/www/wordpress -s /bin/bash "${FTP_USER}"
    echo "${FTP_USER}:${FTP_PASSWORD}" | chpasswd
    chown -R "${FTP_USER}:${FTP_USER}" /var/www/wordpress
fi

exec vsftpd /etc/vsftpd.conf
```

### 4) vsftpd 설정 예시 (`srcs/requirements/bonus/ftp/conf/vsftpd.conf`)
```ini
listen=YES
local_enable=YES
write_enable=YES
local_umask=022
dirmessage_enable=YES
use_localtime=YES
xferlog_enable=YES
connect_from_port_20=YES
chroot_local_user=YES
allow_writeable_chroot=YES
secure_chroot_dir=/var/run/vsftpd/empty
pam_service_name=vsftpd

# Passive Mode 설정 (컨테이너 포트 포워딩 대응)
pasv_enable=YES
pasv_min_port=30000
pasv_max_port=30009
pasv_address=127.0.0.1
```

### 5) Adminer Dockerfile (`srcs/requirements/bonus/adminer/Dockerfile`)
```dockerfile
FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php7.4-fpm \
    php7.4-mysql \
    curl \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/adminer && \
    curl -L -o /var/www/adminer/index.php https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php

# PHP-FPM 실행 디렉토리 구성
RUN mkdir -p /run/php

EXPOSE 9000

# PHP-FPM 포그라운드 실행 (NGINX가 fastcgi를 통해 9000으로 프록싱)
ENTRYPOINT ["/usr/sbin/php-fpm7.4", "-F"]
```

### 6) NGINX 설정 내 보너스 라우팅 병합 (`srcs/requirements/nginx/conf/nginx.conf`)
```nginx
# Adminer 리버스 프록시 라우팅 추가
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

---

## 5. 전용 검증 프롬프트 세트

### [검증 프롬프트 1 - 보너스 서비스 격리도 분석]
> Antigravity, 새로 구성한 보너스 파트의 `docker-compose.yml` 볼륨 및 네트워크 정의를 정적 분석하여, `redis`, `ftp`, `adminer` 서비스들이 모두 단일 커스텀 브리지 네트워크(`inception-network`) 내부에서 구동되는지 확인하고, `ftp` 서비스가 포트 `21` 및 Passive 포트 대역(`30000-30009`)을 올바르게 호스트로 개방해 두었는지 린팅해줘.

### [검증 프롬프트 2 - NGINX 라우팅 및 리버스 프록시 연계 검증]
> Antigravity, NGINX 설정 파일인 `nginx.conf`를 조사하여, `adminer` 및 `static` 웹페이지로의 진입 경로가 올바른 `location` 블록 및 `fastcgi_pass`로 정의되어 외부 침투로부터 격리된 채 TLS (443 포트)만을 거치도록 보장하고 있는지 검증 결과를 설명해줘.

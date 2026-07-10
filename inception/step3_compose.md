# Step 3: docker-compose 및 인프라 레이어 (Docker Compose & Infrastructure Layer)

## 1. 해당 단계의 개요 및 마일스톤 계획
본 단계는 독립된 Docker 컨테이너들을 단일 인프라 스택으로 묶어 실행하는 `docker-compose.yml` 파일을 설계하고 검증하는 과정입니다. 과제 규정에 부합하도록 금지 옵션 사용 여부를 엄격히 확인하고, 데이터가 영구적으로 보존되는 로컬 드라이버 기반의 네임드 볼륨(Named Volume)과 커스텀 브리지 네트워크의 작동 방식을 확립합니다.

### 마일스톤 계획
1. **Compose 파일 구조 설계**: NGINX, MariaDB, WordPress 세 서비스를 컨테이너 레벨로 오케스트레이션.
2. **커스텀 브리지 네트워크 설정**: 서비스 디스커버리를 제공할 격리된 이더넷 서브넷 설계.
3. **네임드 볼륨 생성 및 물리 주소 매핑**: 호스트 내 `/home/sisung/data/` 디렉토리에 정확하게 물리 볼륨을 연결하는 Local Bind 메커니즘 적용.
4. **금지 옵션 배제 정적 린팅**: `links`, `network_mode: host` 등이 하드코딩되지 않았는지 전수 조사.

---

## 2. 필수 핵심 개념 정리

### Docker Bridge Network의 DNS 서비스 디스커버리 원리
* **디폴트 네트워크와 사용자 정의 브리지 네트워크의 차이**: Docker 디폴트 브리지 네트워크(`bridge`)는 컨테이너 간 IP 주소 기반 통신만 제공하며 상호 간 이름 해석(Name Resolution)을 지원하지 않습니다. 반면, 사용자 정의 브리지 네트워크(User-defined Bridge Network)는 내장된 임베디드 DNS 서버(`127.0.0.11`)를 통해 컨테이너 이름을 도메인 이름(FQDN)으로 변환해 줍니다.
* **통신 원리**: WordPress 컨테이너에서 `mariadb` 서버로 통신하고자 할 때, 내장 DNS가 `mariadb`라는 이름을 컨테이너의 동적 IP 주소(예: `172.18.0.3`)로 매핑하여 요청을 자동 전달합니다. 따라서 환경 설정 파일에 동적 IP를 고정하지 않고 서비스 식별자 명칭만으로 종속성을 유지할 수 있습니다.

### 호스트 경로 바인딩(Bind Mount)과 Docker Named Volume(driver_opts bind)의 데이터 영속성 차이점
* **호스트 경로 바인딩 (Bind Mount)**: 호스트의 특정 절대 경로(예: `-v /host/path:/container/path`)를 컨테이너 내부에 직접 마운트합니다. 호스트 파일 시스템의 레이아웃과 보안 속성에 강하게 종속되며, 이 방식은 Inception 서브젝트에서 단독 사용이 불허됩니다.
* **네임드 볼륨 (Named Volume)**: Docker 엔진이 볼륨의 생명주기를 완벽하게 제어합니다. 볼륨명과 연결 메커니즘을 추상화하여 관리하므로 이식성이 뛰어납니다.
* **`driver_opts bind` 물리 매핑 기법**: Named Volume의 이점을 취하면서도 서브젝트 명세인 "호스트의 `/home/login/data` 내에 저장해야 한다"는 제약을 충족하기 위해 `driver: local` 하위에 `o: bind`, `type: none`, `device: /home/login/data` 구조를 결합합니다. 이를 통해 볼륨 삭제(Prune) 시 Docker 내부 캐시뿐 아니라 호스트의 지정된 물리 저장 디렉토리와 직접 동기화되어 완전한 데이터 영속성을 보장합니다.

---

## 3. 상세 할 일 목록 (To-Do List)

- [ ] **docker-compose.yml 내 서비스 정의**
  * NGINX, MariaDB, WordPress 서비스 선언.
  * 컨테이너 빌드 컨텍스트(`context`, `dockerfile`) 설정.
  * `container_name` 명시 및 `restart: always` 적용.

- [ ] **커스텀 네트워크 명시**
  * 하단 `networks`에 `driver: bridge` 유형의 사용자 정의 네트워크 선언.
  * 서비스마다 네트워크 할당.
  * `network_mode: host` 배제 및 `links:` 사용 금지 확인.

- [ ] **Named Volume 매핑 설정**
  * 데이터베이스 볼륨: `mariadb-data` 네임드 볼륨 설정 및 호스트 `/home/sisung/data/mariadb` 경로 연계.
  * 웹 애플리케이션 볼륨: `wordpress-data` 네임드 볼륨 설정 및 호스트 `/home/sisung/data/wordpress` 경로 연계.
  * `driver_opts` 내의 `device` 경로가 정확히 `/home/sisung/data/...`인지 확인.

---

## 4. 정확한 설정 파일 예시 및 코드 스니펫

### 완성형 docker-compose.yml (`srcs/docker-compose.yml`)
```yaml
version: '3.8'

services:
  mariadb:
    build:
      context: ./requirements/mariadb
      dockerfile: Dockerfile
    container_name: mariadb
    restart: always
    env_file:
      - .env
    volumes:
      - mariadb-data:/var/lib/mysql
    networks:
      - inception-network

  wordpress:
    depends_on:
      - mariadb
    build:
      context: ./requirements/wordpress
      dockerfile: Dockerfile
    container_name: wordpress
    restart: always
    env_file:
      - .env
    volumes:
      - wordpress-data:/var/www/wordpress
    networks:
      - inception-network

  nginx:
    depends_on:
      - wordpress
    build:
      context: ./requirements/nginx
      dockerfile: Dockerfile
    container_name: nginx
    restart: always
    ports:
      - "443:443"
    volumes:
      - wordpress-data:/var/www/wordpress
    networks:
      - inception-network

networks:
  inception-network:
    driver: bridge

volumes:
  mariadb-data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/sisung/data/mariadb
  wordpress-data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/sisung/data/wordpress
```

---

## 5. 전용 검증 프롬프트 세트

### [검증 프롬프트 1 - 금지 옵션 정적 린팅 및 검사]
> Antigravity, `/home/sisung/workspace/42cursus/inception/srcs/docker-compose.yml` 파일을 파싱하여 다음 세 가지 금지 사항에 위배되지 않는지 검사해줘.
> 1. `links:` 키워드가 정의되어 있는가?
> 2. `network_mode:` 또는 `host` 모드 관련 키워드가 선언되어 있는가?
> 3. 단순 경로 매핑(`- /host/path:/container/path` 형태의 바인드 마운트)이 볼륨 영역에 포함되어 있는가?

### [검증 프롬프트 2 - 호스트 경로 매핑 정규식 분석]
> Antigravity, `docker-compose.yml` 하단의 `volumes` 구문에서 `driver_opts` 아래 `device` 설정에 적용된 하드웨어 바인딩 경로가 `/home/sisung/data`로 명확하게 일치하는지 정적 조사를 진행하고, 사용자명 `sisung`에 매핑된 최종 구성 경로가 틀린 부분이 없는지 검증 결과를 출력해줘.

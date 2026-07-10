# Step 5: 빌드 및 디펜스 검증 (Build & Defense Validation)

## 1. 해당 단계의 개요 및 마일스톤 계획
본 단계는 완성된 Docker Compose 스택을 Makefile을 통해 자동으로 빌드하고 구동한 후, 서브젝트 명세 조건들이 실제 인프라 레벨에서 올바르게 가동 중인지 동작 검증을 수행하는 최종 확인 단계입니다. 평가 프로세스(디펜스) 시나리오에 대비한 동작 증명 도구의 운용 지침을 담고 있습니다.

### 마일스톤 계획
1. **Makefile 자동화 구축**: 호스트 데이터 보존 디렉토리를 자동 생성하고 빌드와 배포를 단일 명령으로 처리하는 Makefile 스크립트 작성.
2. **컨테이너 가동 라이프사이클 테스트**: 스택 전체를 기동하고 `restart: always` 정책의 정상 가동 테스트 진행.
3. **디펜스 대응 PID 1 검증 스키마**: 실제 평가 위원 및 동료들 앞에서 실행 중인 NGINX, MariaDB, WordPress 컨테이너의 PID 1 프로세스를 출력하는 증명 기법 숙달.

---

## 2. 필수 핵심 개념 정리

### 컨테이너 런타임 수명 주기와 restart: always 상태 코드 제어
* **컨테이너 수명 주기**: 컨테이너는 PID 1이 종료되면 정지(Exited) 상태가 됩니다.
* **`restart: always`의 기능**: 컨테이너가 수동으로 종료(docker stop 등)되었거나 예기치 않게 0이 아닌 에러 코드를 리턴하고 크래시(Crash)가 났을 때, Docker 엔진이 자동으로 해당 컨테이너를 재시작하는 정책입니다.
* **Hacky Patches와의 상관관계**: 이전 단계에서 다룬 바와 같이, 만일 PID 1이 실제 데몬이 아닌 `tail -f`나 `sleep infinity`일 경우 실제 웹 서버 데몬이 비정상 종료(0 이외의 종료 코드)되더라도 컨테이너 자체는 멈추지 않고 계속 실행(Up) 중으로 판정되어 `restart: always`가 트리거되지 않습니다. 따라서 PID 1을 실제 단일 데몬으로 일치시키는 것이 인프라 자동 모니터링 및 복구의 필수적 전제 조건입니다.

---

## 3. 상세 할 일 목록 (To-Do List)

- [ ] **디바이스 볼륨 연동을 위한 호스트 경로 생성 자동화**
  * Makefile 내 `build` 타겟 진입 시 `mkdir -p` 구문을 활용해 `/home/sisung/data/wordpress` 및 `/home/sisung/data/mariadb` 자동 생성.

- [ ] **Docker Compose 라이프사이클 제어 타겟 구현**
  * `all`, `build`, `up`, `down`, `re`, `clean`, `fclean` 등 필수 빌드 오퍼레이션 규격 정의.

- [ ] **런타임 PID 1 프로세스 진단 기법 훈련**
  * `docker exec`와 `ps -ef` 명령 조합으로 각 서비스의 프로세스 제어 상태 실시간 파악.

- [ ] **호스트 네트워크 격리 상태 검증**
  * 외부로 노출되는 포트가 오직 NGINX의 `443` 포트뿐인지 호스트 머신에서 포트 포워딩 상태 조사 (`docker ps` 및 `ss -tulpn`).

---

## 4. 정확한 설정 파일 예시 및 코드 스니펫

### 완성형 Makefile (`Makefile`)
```makefile
NAME = inception

SRCS_DIR = ./srcs
DOCKER_COMPOSE = docker-compose -f $(SRCS_DIR)/docker-compose.yml

# 기본 실행: 환경 빌드 및 구동
all: build up

# 호스트 물리 볼륨 디렉토리를 선제 생성한 후 빌드 실행
build:
	@echo "[INFO] Creating host persistent directories..."
	@mkdir -p /home/sisung/data/wordpress
	@mkdir -p /home/sisung/data/mariadb
	@echo "[INFO] Commencing container images build..."
	@$(DOCKER_COMPOSE) build

# 백그라운드로 컨테이너 스택 기동
up:
	@echo "[INFO] Launching service containers..."
	@$(DOCKER_COMPOSE) up -d

# 컨테이너 서비스 정지
down:
	@echo "[INFO] Stopping service containers..."
	@$(DOCKER_COMPOSE) down

# 컨테이너 정지 및 미사용 리소스 정리
clean: down
	@echo "[INFO] Cleaning docker system artifacts..."
	@docker system prune -a -f

# 완전 삭제 (볼륨 보존 폴더 삭제 포함)
fclean: clean
	@echo "[INFO] Removing host data directories..."
	@sudo rm -rf /home/sisung/data

# 전체 리빌드 실행
re: fclean all

.PHONY: all build up down clean fclean re
```

---

## 5. 이 단계를 진행할 때 안티그래비티(본 IDE)에 입력하여 코드를 교차 검증할 수 있는 '전용 검증 프롬프트' 세트

### [검증 프롬프트 1 - 디펜스 준비용 PID 1 프로세스 모니터링 스크립트 실행]
> Antigravity, 각 실행 중인 컨테이너 내부의 프로세스 구동 정보를 조회하기 위해, 터미널 명령을 제안 또는 실행해줘. `mariadb`, `nginx`, `wordpress` 컨테이너 각각에 대해 `ps -ef` 또는 `ps aux` 명령을 전송하여 PID 1이 쉘 스크립트가 아닌 각 서비스 데몬(nginx master, mysqld, php-fpm)으로 완벽하게 전면 구동 중인지 파싱하고 분석 보고를 제출해줘.

### [검증 프롬프트 2 - 포트 바인딩 및 네트워크 침투 노출 진단]
> Antigravity, 컨테이너 네트워크 보안 요건을 평가하기 위해, 외부로 개방된 호스트 포트가 오직 NGINX의 `443`만 존재하는지 검사해줘. `mariadb` 컨테이너의 3306 포트나 `wordpress` 컨테이너의 9000 포트가 외부 호스트 머신에서 직접 접속 불가능하도록 구성되어 포트 차단이 성공했는지 정적 `docker-compose.yml` 포트 바인딩 속성을 검사하여 타당성을 진단해줘.

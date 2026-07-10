# Step 4: 보안 및 데이터 격리 (Security & Data Isolation)

## 1. 해당 단계의 개요 및 마일스톤 계획
본 단계는 데이터베이스 패스워드, 관리자 크리덴셜 등 민감 정보가 소스코드 관리 시스템(Git)이나 불필요한 빌드 결과물에 노출되는 것을 완전 차단하는 보안 심화 단계입니다. 환경 변수와 Docker Secrets의 차이점을 고찰하고, 계정 생성 정책 준수 여부 및 하드코딩된 크리덴셜 정적 분석 기법을 실천합니다.

### 마일스톤 계획
1. **.env 환경 구성**: 환경변수 설정 가이드와 로컬 전용 파일 생성.
2. **보안 인증 규칙 적용**: WordPress 관리자 계정에 대한 키워드 필터링(admin 금지 규칙).
3. **Git 노출 완전 방지**: 민감 파일에 대한 `.gitignore` 보안 패턴 등록.
4. **정적 패스워드 하드코딩 검침**: IDE 정적 분석 도구를 사용해 코드 내 하드코딩 패스워드 잔존 여부 전수 검사.

---

## 2. 필수 핵심 개념 정리

### 환경 변수(.env)와 Docker Secrets의 기술적 보안 차이점
* **환경 변수 (.env) 방식**:
  - `docker-compose` 빌드 및 컨테이너 런타임 내에 문자열 상수로 환경 변수를 주입합니다.
  - 컨테이너 내부에서 `env` 또는 `printenv` 명령어를 통해 환경 변수가 노출되며, 프로세스가 구동된 후 `/proc/1/environ` 경로를 통해서도 일반 텍스트 상태로 노출되므로 탈취 위험도가 높습니다.
* **Docker Secrets 방식 (강력 권장)**:
  - Docker Swarm 또는 Compose Spec 최신 사양에서 사용되는 비밀 데이터 격리 기법입니다.
  - 민감 정보 파일(예: `db_password.txt`)을 개별 파일로 분리하여 보관하며, 컨테이너 내부 가상 메모리 파일 시스템(tmpfs)인 `/run/secrets/` 경로 하위에 가상 파일 형태로 임시 마운트됩니다.
  - 디스크에 기입되지 않고 온메모리 기반 파일 리딩 형태로만 프로세스에 접근 권한을 허용하기 때문에 호스트 환경의 침투 위협으로부터 안전하게 격리됩니다.

### WordPress 관리자 계정 생성 시 이름 검증 규칙
* **서브젝트 요구 조건**: WordPress 데이터베이스 초기 구성 시, 사이트 전체 권한을 가지는 총 관리자(Administrator) 계정의 계정명에는 **`admin`**, **`Admin`**, **`administrator`**, **`Administrator`** 등 유사 단어가 포함될 수 없습니다.
* **위반 시 판정**: 평가 표준 가이드라인에 따라 관리자 이름에 위 키워드가 포함될 경우 보안 모범 사례 위반으로 처리되어 감점 없이 즉시 Fail 처리되는 실격 요건입니다. 반드시 `wp_admin` 등 대신 `sisung_owner`, `super_user` 등 임의의 고유 ID를 부여해야 합니다.

---

## 3. 상세 할 일 목록 (To-Do List)

- [ ] **.env 템플릿 작성 및 배치**
  * `srcs/.env` 경로에 필요한 비밀키 명칭 설정.
  * 외부 유출 방지를 위한 예시 데이터 기입.

- [ ] **.gitignore 보안 필터 적용**
  * 프로젝트 루트(`/home/sisung/workspace/42cursus/inception/`)에 `.gitignore` 작성.
  * `.env` 및 `secrets/` 파일군 등록으로 커밋 누출 사전 예방.

- [ ] **WordPress 관리자 이름 검증**
  * `.env` 설정의 `WP_ADMIN_USER` 항목에서 `admin` 계열 단어 원천 제거.
  * `wordpress_setup.sh` 내부의 `wp core install` 명령어에 올바른 변수가 매핑되었는지 점검.

- [ ] **하드코딩 패스워드 탐색 및 격리**
  * Antigravity IDE의 `grep_search` 도구 또는 정규식을 통해 `srcs/` 내 소스코드 파일에서 `password=`, `pass=` 등의 리터럴 대입 구문 추출 및 정화.

---

## 4. 정확한 설정 파일 예시 및 코드 스니펫

### 1) 환경 변수 파일 예시 (`srcs/.env`)
```env
DOMAIN_NAME=sisung.42.fr

# MySQL 데이터베이스 자격 정보
MYSQL_DATABASE=inception_db
MYSQL_USER=wp_db_user
MYSQL_PASSWORD=secure_user_pass123
MYSQL_ROOT_PASSWORD=secure_root_pass987

# WordPress 계정 정보 (주의: 관리자 계정에 'admin' 키워드 절대 금지)
WP_ADMIN_USER=sisung_master
WP_ADMIN_PASSWORD=master_secret_key_42
WP_USER=sisung_regular
WP_USER_PASSWORD=regular_secret_key_42
```

### 2) Git 형상 관리 무시 파일 설정 (`.gitignore`)
```list
# Local environment credentials
srcs/.env

# Local secret files
secrets/
*.txt

# Build cache and system files
.DS_Store
*.swp
*.log
```

---

## 5. 전용 검증 프롬프트 세트

### [검증 프롬프트 1 - 관리자 이름 보안 준수도 평가]
> Antigravity, `.env` 파일과 `wordpress_setup.sh` 파일을 동시에 정적 조사하여, 관리자 사용자 이름을 결정하는 변수인 `WP_ADMIN_USER`의 대입 문자열 값에 `admin` 혹은 `administrator` 문자열(대소문자 무관)이 발견되는지 확인하고, 해당 보안 규칙에 위배될 경우 경고 리포트를 발송해줘.

### [검증 프롬프트 2 - 민감정보 하드코딩 정규식 스캔]
> Antigravity, `grep_search` 도구를 활용하여 `/home/sisung/workspace/42cursus/inception/srcs` 디렉토리 아래의 `Dockerfile`, `nginx.conf`, `.sh` 쉘 스크립트 파일을 스캔해줘. 정규식 패턴 `(PASSWORD|PASS|SECRET|KEY)\s*=\s*['"]?[a-zA-Z0-9_\-]+['"]?`을 사용해서 환경 변수 변수명이 아닌 리터럴 문자열 비밀번호가 직접 하드코딩되어 대입된 흔적을 검색해줘.

# Step 1: 환경 구성 및 인덱싱 (Environment Setup & Indexing)

## 1. 해당 단계의 개요 및 마일스톤 계획
본 단계는 Inception 프로젝트 수행을 위한 개발 환경을 구축하고 프로젝트 표준 디렉토리 구조를 구조화하는 초기 단계입니다. 가상 머신(VM) 환경의 격리 수준과 사용되는 쉘 환경의 원리를 이해하여 안정적인 인프라 배포의 기반을 마련합니다.

### 마일스톤 계획
1. **VM 가상화 검증**: 호스트 OS와 VM 간 격리 상태 및 네트워크 구성 확인.
2. **쉘 환경 구성**: VM 내 Fish Shell 설치 및 최적화(자동 제안 기능 포함).
3. **디렉토리 스캐폴딩**: 서브젝트 요구사항을 만족하는 표준 디렉토리 구조 자동 생성.
4. **IDE 컨텍스트 인덱싱**: Antigravity IDE가 프로젝트 디렉토리 구조와 서브젝트 제약 조건을 학습하도록 인덱싱 구성.

---

## 2. 필수 핵심 개념 정리

### 가상 머신(VM)과 호스트 OS의 격리 메커니즘
* **하드웨어 가상화 (Type-2 Hypervisor)**: Inception 프로젝트는 VirtualBox/VMware 등 하이퍼바이저 위에서 구동되는 가상 머신 내에서 수행됩니다. VM은 호스트 OS의 커널을 공유하지 않으며, 독자적인 게스트 OS 커널, 가상 CPU, 가상 메모리 및 가상 네트워크 인터페이스(NIC)를 가집니다.
* **커널 레벨 격리**: VM 내부의 프로세스는 하드웨어 수준에서 독립된 메모리 주소 공간(Nested Page Tables)과 CPU 실행 권한 링(Ring 0/Ring 3)을 가지므로 호스트 OS 커널에 직접적인 영향을 주지 못하며 완전히 격리됩니다.
* **네트워크 격리**: VM은 NAT(Network Address Translation) 또는 Bridge 어댑터를 통해 호스트 OS와 구별되는 가상 서브넷 IP 대역을 할당받습니다.

### Fish Shell 작동 원리 및 자동 제안(Autosuggestions) 설정 메커니즘
* **Fish Shell의 특징**: Friendly Interactive Shell(Fish)은 POSIX 비호환 쉘이지만, 기본적 구문 강조(Syntax Highlighting) 및 자동 제안(Autosuggestions) 기능을 내장하여 개발 생산성을 향상시킵니다.
* **Autosuggestions 작동 메커니즘**: Fish Shell은 사용자가 입력한 명령어 히스토리(`~/.local/share/fish/fish_history`)를 기반으로 현재 입력 중인 접두사(Prefix)와 가장 일치하는 과거의 명령어를 실시간 탐색합니다. 일치하는 완성본을 옅은 회색으로 셸 버퍼 상에 표시하며, `Right Arrow` 키 또는 `Ctrl+F` 키 입력을 통해 완성된 명령을 수락할 수 있습니다.
* **설정 파일 위치**: 사용자별 영구 설정은 `~/.config/fish/config.fish` 파일에 작성되며, 구문 가독성 제어와 자동완성 스크립트는 `~/.config/fish/functions/` 디렉토리에 저장됩니다.

---

## 3. 상세 할 일 목록 (To-Do List)

- [ ] **Fish Shell 패키지 설치 및 기본 셸 설정**
  * VM 내 패키지 관리 도구(apt 등)를 통해 Fish Shell 설치 및 로그인 기본 셸 변경.
  * `sudo apt update && sudo apt install -y fish`
  * `chsh -s /usr/bin/fish` (사용자 로그아웃 후 재로그인 필요)

- [ ] **표준 디렉토리 트리 구조 스캐폴딩**
  * Inception 프로젝트 루트 디렉토리 `/home/sisung/workspace/42cursus/inception` 내에 필수 서브 디렉토리 구축.
  * `mkdir -p srcs/requirements/nginx/conf srcs/requirements/nginx/tools`
  * `mkdir -p srcs/requirements/mariadb/conf srcs/requirements/mariadb/tools`
  * `mkdir -p srcs/requirements/wordpress/conf srcs/requirements/wordpress/tools`

- [ ] **호스트 마운트 데이터 디렉토리 생성**
  * Docker Named Volume의 호스트 바인딩 대상 디렉토리 사전에 생성.
  * `mkdir -p /home/sisung/data/wordpress`
  * `mkdir -p /home/sisung/data/mariadb`

- [ ] **설정 파일 파일 스캐폴딩**
  * 각 서비스별 설정 파일 위치 확보를 위한 빈 파일 생성.
  * `touch srcs/docker-compose.yml srcs/.env`
  * `touch srcs/requirements/nginx/conf/nginx.conf`
  * `touch srcs/requirements/mariadb/conf/50-server.cnf`
  * `touch srcs/requirements/wordpress/conf/www.conf`

---

## 4. 정확한 설정 파일 예시 및 코드 스니펫

### Fish Shell 영구 설정 (`~/.config/fish/config.fish`)
```fish
if status is-interactive
    # 에일리어스 설정
    alias dps="docker ps --format 'table {{.Names}}\t{{.Status}}\t{{.Ports}}'"
    alias dcomp="docker-compose -f /home/sisung/workspace/42cursus/inception/srcs/docker-compose.yml"
    
    # Fish Shell 자동 제안 단축키 수락 설정 (Ctrl+F 또는 Right Arrow로 전체 자동완성 적용)
    bind \cf forward-char
end
```

### 디렉토리 스캐폴딩 자동화 쉘 스크립트 (`setup_workspace.sh`)
```bash
#!/bin/bash
set -e

WORKSPACE_ROOT="/home/sisung/workspace/42cursus/inception"

echo "[INFO] Creating standard Inception directory layout..."
mkdir -p ${WORKSPACE_ROOT}/srcs/requirements/nginx/conf
mkdir -p ${WORKSPACE_ROOT}/srcs/requirements/nginx/tools
mkdir -p ${WORKSPACE_ROOT}/srcs/requirements/mariadb/conf
mkdir -p ${WORKSPACE_ROOT}/srcs/requirements/mariadb/tools
mkdir -p ${WORKSPACE_ROOT}/srcs/requirements/wordpress/conf
mkdir -p ${WORKSPACE_ROOT}/srcs/requirements/wordpress/tools

echo "[INFO] Creating host persistent volume data paths..."
mkdir -p /home/sisung/data/wordpress
mkdir -p /home/sisung/data/mariadb

echo "[INFO] Directory tree creation completed successfully."
ls -laR ${WORKSPACE_ROOT}/srcs
```

---

## 5. 전용 검증 프롬프트 세트

### [검증 프롬프트 1 - 디렉토리 정적 검사]
> Antigravity, `/home/sisung/workspace/42cursus/inception` 디렉토리 아래의 전체 트리 구조를 스캔하고, `srcs/requirements/nginx/conf`, `srcs/requirements/mariadb/conf`, `srcs/requirements/wordpress/conf` 디렉토리가 모두 누락 없이 정상적으로 구성되어 있는지 정적 분석하여 그 결과를 보고해줘.

### [검증 프롬프트 2 - 환경 격리 및 셸 무결성 검증]
> Antigravity, 현재 시스템의 기본 로그인 셸이 `/usr/bin/fish`로 지정되어 있는지 `/etc/passwd` 파일을 검사하고, 호스트 데이터 디렉토리인 `/home/sisung/data/wordpress` 및 `/home/sisung/data/mariadb` 디렉토리의 소유권(Owner)과 권한(Permission) 상태를 진단하여 보고해줘.

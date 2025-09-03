# Minitalk

## 📌 프로젝트 목적
`Minitalk`은 **UNIX 시그널(`SIGUSR1`, `SIGUSR2`)**만을 사용하여 **클라이언트와 서버 간의 양방향 통신**을 구현하는 프로젝트입니다.
이 과제를 통해 저수준 프로세스 간 통신(IPC, Inter-Process Communication)을 이해하고, 시그널 기반 데이터 전송의 한계와 특징을 학습하는 것을 목표로 합니다.

---

## 📖 과제 개요
- **서버 (`server`)**
  - 실행 시 자신의 PID를 출력합니다.
  - 클라이언트로부터 시그널을 통해 전송된 메시지를 수신하고 출력합니다.
  - 여러 클라이언트의 메시지를 순차적으로 처리할 수 있어야 합니다.

- **클라이언트 (`client`)**
  - 실행 시 인자로 **서버 PID**와 **전송할 문자열**을 받습니다.
  - 문자열을 비트 단위로 변환하여 시그널(`SIGUSR1`, `SIGUSR2`)을 서버로 전송합니다.
  - 보너스 파트에서는 서버로부터 **응답 시그널**을 받아 전송 완료 여부를 확인합니다.

- **통신 방식**
  - `SIGUSR1`, `SIGUSR2` 두 가지 시그널만 사용.
  - 서버는 시그널을 통해 수신한 비트를 문자 단위로 재조립하고 문자열을 완성합니다.

- **규칙**
  - 실행 파일 이름은 반드시 `server`, `client`.
  - 허용 함수:
    `write`, `signal`, `sigaction`, `kill`, `getpid`,
    `malloc`, `free`, `pause`, `sleep`, `usleep`, `exit`,
    `libft에 구현된 함수`.

---

## ⚙️ 구현 단계

### 1단계: 서버 구현
- [x] `getpid()`로 서버 PID 출력
- [x] `sigaction()`으로 시그널 핸들러 등록
- [ ] 시그널을 비트 단위로 모아 문자를 재조립
- [ ] 전체 문자열 출력
- [x] 무한 대기 루프 (`pause()` 또는 `while (1)`)

### 2단계: 클라이언트 구현
- [ ] 인자 검사 (서버 PID, 문자열)
- [ ] 문자열을 비트 단위로 변환
- [ ] `kill()`을 이용해 비트별 시그널 전송
- [ ] `usleep()`으로 전송 간 지연 추가

### 3단계: 보너스 구현
- [ ] **서버 응답**: 서버는 메시지를 다 받은 후, `kill()`을 사용하여 클라이언트에게 확인 신호(`SIGUSR1`) 전송
- [ ] **클라이언트 응답 처리**: 클라이언트는 서버로부터 응답을 수신하고 `"Message received!"` 같은 로그 출력
- [ ] **UTF-8 지원**: 다바이트 이상 문자를 비트 단위로 올바르게 전송/재조립하도록 구현
- [ ] 여러 클라이언트가 동시에 요청했을 때의 경쟁 조건 처리 (선택적 개선 사항)

---

## 🐞 디버깅 히스토리
- **문제**: 클라이언트에서 시그널을 너무 빠르게 전송하여 서버가 놓침
  **해결**: `usleep()` 추가하여 비트 전송 간격 확보
- **문제**: 서버가 문자열 끝(`\0`)을 출력하지 않아 무한 루프 발생
  **해결**: 문자열 종료 문자(`\0`)까지 전송 및 출력 처리
- **문제**: 다바이트 UTF-8 문자 깨짐
  **해결**: `unsigned char`로 비트 변환 및 조립 시 오버플로 방지
- **문제**: 서버가 메시지 수신 완료를 알리지 않아 클라이언트 상태 불명확
  **해결**: 서버 → 클라이언트 응답 시그널 구현

---

## 📂 디렉토리 구조
```bash
minitalk/
├── Makefile
├── include/
│   └── minitalk.h
├── src/
│   ├── client.c
│   ├── server.c
│   ├── utils.c
│   └── bonus/
│       ├── client_bonus.c
│       ├── server_bonus.c
│       └── utils_bonus.c
└── README.md
```

---

## 🔨 빌드 및 실행 방법

### 빌드

```bash
make        # server와 client 실행 파일 생성
make bonus  # 보너스 버전(server_bonus, client_bonus) 생성
make clean  # 오브젝트 파일 삭제
make fclean # 실행 파일 및 오브젝트 파일 삭제
make re     # 전체 재빌드
```

### 실행

#### 필수 파트

1. 서버 실행

```bash
./server
# PID 출력
```

2. 클라이언트 실행

```bash
./client [서버 PID] "Hello World"
```

#### 보너스 파트

1. 서버 실행

```bash
./server_bonus
# PID 출력
```

2. 클라이언트 실행

```bash
./client_bonus [서버 PID] "안녕하세요 😀"
```

3. 실행 결과 예시

```bash
$ ./server_bonus
Server PID: 12345
Hello World
안녕하세요 😀

$ ./client_bonus 12345 "Hello World"
Message received!
```

---

## ✅ 제출 점검 리스트

* [ ] 서버 실행 시 PID 출력
* [ ] 클라이언트 → 서버 메시지 전송 성공
* [ ] 여러 클라이언트 메시지 연속 수신 가능
* [ ] 잘못된 인자/유효하지 않은 PID 입력 시 예외 처리
* [ ] Norm 규칙 준수
* [ ] 메모리 누수 없음
* [ ] Makefile 규칙(`all`, `clean`, `fclean`, `re`, `bonus`) 정상 동작
* [ ] 보너스: 서버 ↔ 클라이언트 응답 시그널
* [ ] 보너스: UTF-8 문자 처리

---

## 📚 참고

* UNIX 시그널 매뉴얼: `man 2 kill`, `man 2 sigaction`, `man 7 signal`
* 42 과제 PDF: Minitalk Subject

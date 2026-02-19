# 📦 Sandbox - Process Monitoring Tool

42 Exam 04의 Level 1 과제입니다. 특정 함수(`f`)를 자식 프로세스에서 실행하고, 해당 함수의 **실행 결과 및 생존 여부**를 안전하게 감시(Sandboxing)하는 프로그램을 구현했습니다.

---

## 🚀 개요

이 프로젝트의 목적은 프로세스 제어 시스템 콜(`fork`, `waitpid`)과 시그널 메커니즘(`alarm`)을 활용하여 신뢰할 수 없는 코드를 격리된 환경에서 실행하는 것입니다.

### 함수 프로토타입

```c
#include <stdbool.h>
int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

```

---

## 🛠️ 핵심 로직

함수는 다음과 같은 **3단계 격리 메커니즘**으로 작동합니다:

1. **격리 (Isolation)**: `fork()`를 사용하여 부모 프로세스와 독립된 자식 프로세스를 생성합니다.
2. **제한 (Constraint)**: `alarm(timeout)`을 설정하여 자식 프로세스가 무한 루프에 빠지더라도 특정 시간 후 종료되도록 강제합니다.
3. **분석 (Analysis)**: 부모 프로세스는 `waitpid()`를 통해 자식의 종료 상태(`status`)를 수거하고, 매크로를 사용하여 사망 원인을 분석합니다.

---

## 📊 판별 기준 및 반환값

`sandbox`는 자식 프로세스의 종료 상태에 따라 다음과 같은 값을 반환합니다.

| 상태 | 조건 | 반환값 | `verbose` 메시지 |
| --- | --- | --- | --- |
| **Nice** | 정상 종료 (Exit Code 0) | `1` | `Nice function!` |
| **Bad (Exit)** | 정상 종료되었으나 에러 코드 발생 | `0` | `Bad function: exited with code <exit_code>` |
| **Bad (Signal)** | 시그널에 의해 종료 (Segfault 등) | `0` | `Bad function: <signal description>` |
| **Bad (Timeout)** | 설정된 시간 초과 (`SIGALRM`) | `0` | `Bad function: timed out after <timeout> seconds` |
| **Error** | 시스템 콜 실패 (fork 에러 등) | `-1` | (메시지 없음) |

---

## 📚 사용된 시스템 콜 (Allowed Functions)

* **Process**: `fork`, `waitpid`, `exit`
* **Signals**: `alarm`, `sigaction`, `kill`, `strsignal`
* **Signal Sets**: `sigaddset`, `sigemptyset`, `sigfillset`, `sigdelset`, `sigismember`
* **Others**: `printf`, `errno`

---

## 💻 테스트 방법

자체적으로 제작한 테스트 메인 문을 통해 다양한 에러 케이스를 검증할 수 있습니다.

```c
// 예시 테스트 함수들
void segfault_func() { int *p = NULL; *p = 42; }
void timeout_func() { while(1); }
void exit_42_func() { exit(42); }

// 실행 예시
sandbox(segfault_func, 2, true);
// 출력: Bad function: Segmentation fault

```

---

## 💡 학습한 점

* `fork()` 이후 부모와 자식 프로세스의 메모리 구조 및 흐름 제어.
* `waitpid` 상태 값(`status`)에서 정보를 추출하는 비트 매크로 활용법.
* `alarm`과 시그널을 이용한 타임아웃 메커니즘 구현.
* `strsignal`을 활용한 사용자 친화적인 에러 메시지 처리.


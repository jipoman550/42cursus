# push_swap

## 📌 프로젝트 목적

> 두 개의 스택(a, b)과 제한된 명령어를 사용하여 stack a를 최소한의 연산으로 오름차순 정렬하는 C 프로그램.

---

## 🧠 과제 개요

 - 인자로 주어진 숫자들을 `stack a`에 넣고, `stack b`를 보조로 사용하여 `stack a`를 정렬한다.
 - 사용 가능한 명령어:
	- **swap**: sa (swap a), sb (swap b), ss (sa + sb)
	- **push**: pa (push a), pb (push b)
	- **rotate**: ra (rotate a), rb (rotate b), rr (ra + rb)
	- **reverse rotate**: rra (reverse rotate a), rrb (reverse rotate b), rrr (rra + rrb)
- 각 명령어는 **표준 출력에 한 줄씩 출력** 되어야 하며, 명령어 개수를 **최대한 줄여야 한다.**
- 벤치 마크

	• For maximum project validation (100%) and eligibility for bonuses, you must:

		◦ Sort 100 random numbers in fewer than 700 operations.

		◦ Sort 500 random numbers in no more than 5500 operations.

	• For minimal project validation (which implies a minimum grade of 80%), you can succeed with different averages:

		◦ 100 numbers in under 1100 operations and 500 numbers in under 8500 operations

		◦ 100 numbers in under 700 operations and 500 numbers in under 11500 operations

		◦ 100 numbers in under 1300 operations and 500 numbers in under 5500 operations

		...

---

## 🚀 구현 계획 및 진행 상황

### 1단계: 입력 처리 및 유효성 검사
- [v] 문자열을 숫자로 파싱 (atoi 또는 ft_atoi 구현 및 사용)
- [v] 숫자 범위 확인 (INT_MIN ~ INT_MAX 초과 여부 검사)
- [v] 중복 숫자 검사
- [v] 유효하지 않은 입력(비숫자, 빈 문자열 등)에 대한 예외 처리 및 "Error\n" 출력 ?? 터미널 입력 형식? 그러니까 argc, argv일 때 "", '', 그냥 쓰기 이런것도 알아보면 좋을 듯
- [v] 인자가 없는 경우 아무것도 출력하지 않고 종료

### 2단계: 스택 자료구조 구현
- [v] 연결 리스트 기반의 스택 A, B 구성 (노드 구조체, 스택 헤더 구조체 등 정의)
- [v] 기본 스택 연산 함수 구현:
	- [v] new_node 함수 (새로운 node 추가)
	- [v] create_stack 함수 (스택 함수 만들기)
	- [v] push(스택 맨 위에 요소 추가)
	- [v] push(스택 맨 위에 요소 추가)
	- [v] pop(스택 맨 위 요소 제거 및 반환)
	- [v] peek(스택 맨 위 요소 참조)
	- [v] 스택 크기 확인 (ft_lstsize 또는 유사 함수 활용)
	- [v] 스택 비어있는지 확인 (is_empty)
- [v] 스택 메모리 해제 함수 (free_stack) 구현 (메모리 누수 방지)

### 3단계: 명령어 함수 구현
- [v] sa, sb, ss
- [v] pa, pb
- [v] ra, rb, rr
- [v] rra, rrb, rrr
- [v] 각 명령어 실행 후 해당 명령어 문자열을 표준 출력에 출력하는 로직 포함

### 4단계: 정렬 알고리즘
- radix sort 사용
- (다른 전략) chunk 전략, greedy insert, quick sort, sort-merge based on replacement selection, followed by a two-way polyphase merge, etc...
- [ ] 입력 숫자 인덱싱
- [ ] 3개 이하 숫자: 조건 분기
- [ ] 4~5개 숫자: 최소 명령어 조합
- [ ] 100개 이상: radix sort 기반 정렬
- [ ] 메인 정렬 함수 통합
- [ ] 입력된 값이 이미 정렬된 경우

### 5단계. 명령어 출력 시스템
- [ ] 수행된 명령어를 stdout에 한 줄씩 출력
- [ ] 디버깅용 명령어 기록 및 stack 상태 출력 함수 추가 // ?? 3단계에서 명령어 표준출력에 출력하는데, 왜 디버깅용을 따로 또 하는 거임?

### 6단계. 테스트 및 최적화
- [ ] 다양한 입력 시나리오에 대한 정확성 테스트 (checker_OS 사용)
- [ ] 명령어 수 확인 및 벤치마크 목표 달성 여부 검증
- [ ] 메모리 누수 검사: valgrind 및 leaks 도구 활용
- [ ] Norm 규정 준수 여부 최종 확인 (norminette 사용)

---

## 🛠️ 디버깅 및 문제 해결 히스토리

이 섹션은 개발 과정에서 발생한 주요 버그와 그 해결 과정을 기록하여, 향후 유사 문제 발생 시 참고하거나 프로젝트 방어 시 설명 자료로 활용합니다.

=== 1단계 ===
 - 1단계 ./push_swap "1 2 3 4", ./push_swap "1" "2" "3" "4", 둘다 섞은 경우 다 되게 해야됨. 이것을 하면서 문제를 많이 만남.
 - size_t의 활용에 대해

=== 2단계 ===



=== 예시 ===
[2025-07-08] - pa/pb 실행 시 Segmentation Fault

증상: pa 또는 pb 실행 시 스택이 비어있는 경우 NULL 포인터 역참조로 인해 프로그램이 비정상 종료됨.

원인 분석: 스택에서 요소를 pop하거나 push할 때, 대상 스택의 유효성(비어있는지 여부)을 확인하지 않아 발생.

해결 방안: pa 및 pb 함수 내부에 b 스택(또는 a 스택)이 비어있는지 확인하는 조건문을 추가하고, 필요시 작업을 수행하지 않도록 수정.

배운 점: 모든 스택 연산 전에 스택이 비어있는지 또는 필요한 최소한의 요소가 있는지 항상 확인하는 습관의 중요성.

[날짜] - [문제 요약]

증상: (발생 시 기록)

원인 분석: (발생 시 기록)

해결 방안: (발생 시 기록)

배운 점: (발생 시 기록)

---

## 📂 디렉토리 구조 (계획)

<pre><code>
push_swap/
├── Makefile                # 프로젝트 빌드를 위한 Makefile
├── push_swap.c             # main 진입점 (인자 파싱, 초기화, 정렬 알고리즘 호출)
├── includes/
│   └── push_swap.h         # 모든 구조체 정의, 함수 프로토타입 선언
├── src/
│   ├── parsing.c           # 인자 파싱 및 유효성 검사 관련 함수
│   ├── stack_utils.c       # 스택 자료구조 기본 연산 (생성, 삭제, push, pop, peek 등) ?? 삭제랑 생성은 할 필요없지 않나?
│   ├── instructions.c      # sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr 명령어 구현
│   ├── sort_small.c        # 3개, 4개, 5개 숫자 등 작은 입력에 대한 최적화된 정렬 로직 ?? 2개는 무시하냐?
│   ├── sort_large.c        # 100개, 500개 숫자 등 큰 입력에 대한 정렬 알고리즘 (예: Radix Sort)
│   └── utils.c             # 기타 공통적으로 사용되는 유틸리티 함수 (예: 에러 출력, 스택 출력 for 디버깅)
└── libft/                  # (필요시) 프로젝트에서 사용하는 Libft 소스 및 Makefile
 </code></pre>

---

## 빌드방법, 컴파일 명령어,  테스트 명령어

---

## ✅ 최종 제출 점검표

프로그램 동작 (Mandatory)
- [ ] 인자 없을 시 아무것도 출력 안 하고 종료
- [ ] 모든 오류 상황에서 정확히 "Error\n" 출력:
	- 정수가 아닌 인자 (0 one 2 3)
	- 정수 범위 (INT_MIN ~ INT_MAX) 초과 인자
	- 중복된 인자
- [ ] stack a가 오름차순으로 완벽하게 정렬되고, 가장 작은 수가 맨 위에 위치하는지 확인
- [ ] 출력된 명령어 시퀀스가 실제 정렬을 수행하며 checker_OS 프로그램으로 "OK"를 받는지 확인
- [ ] 벤치마크 목표 달성 여부:
	- 100개 숫자: 700회 미만 (최소 1100회 미만)
	- 500개 숫자: 5500회 미만 (최소 8500회 미만)

코드 품질 및 규정 (Norm & Memory)
- [ ] 모든 .c, .h 파일이 Norm 규정을 완벽히 준수하는지 (norminette 통과)
- [ ] valgrind 및 leaks 검사를 통해 메모리 누수가 전혀 없는지 확인
- [ ] 세그멘테이션 폴트, 버스 에러 등 예기치 않은 프로그램 종료 없음
- [ ] 전역 변수 사용 금지 규정 준수
- [ ] 허용되지 않은 외부 함수 사용 여부 재확인 (허용: read, write, malloc, free, exit, ft_printf 또는 동등한 직접 구현 함수)

Makefile
- [ ] $(NAME), all, clean, fclean, re 규칙 모두 정상 작동
- [ ] cc -Wall -Wextra -Werror 플래그 적용 확인
- [ ] 불필요한 재링크 발생 안 함
- [ ] (보너스 구현 시) bonus 규칙 정상 작동

---

## 📝 메모

- [ ] 디버깅용 `print_stack()` 함수는 최종 제출 전 제거
- [ ] 실행파일 이름은 `push_swap`

---
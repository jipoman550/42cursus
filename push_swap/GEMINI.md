1. 각 단계에 대한 설명을 자세히 해줘라.
2. 설명은 따로 영어로 해달라는 요구가 없으면, 다한국어로 해줘라.

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

# push_swap

https://cdn.intra.42.fr/pdf/pdf/163194/en.subject.pdf

https://windowdong11.github.io/push_swap_visualizer/

# I Foreword

언어마다 Hello, world! 출력하는 방법인듯

# II Introduction

The Push swap project is a simple yet highly structured algorithmic challenge: you
need to sort data.

You have at your disposal a set of integer values, 2 stacks, and a set of instructions to
manipulate both stacks.

Your goal? Write a C program called push_swap that calculates and displays the
shortest sequence of Push_swap instructions needed to sort the given integers.
Easy?

We’ll see...

# III Objectives

Writing a sorting algorithm is always a crucial step in a developer’s journey. It is often
the first encounter with the concept of complexity.

Sorting algorithms and their complexities are common topics in job interviews. Now is a great time to explore these concepts, as you will likely encounter them in the future.

The learning objectives of this project are rigor, proficiency in C, and the application of basic algorithms, with a particular focus on their complexity.

Sorting values is straightforward, but finding the fastest way to sort them is more challenging. The most efficient sorting method can vary depending on the arrangement of integers.

# IV Common Instructions

- Your project must be written in C.
- Your project must be written in accordance with the Norm. If you have bonus  files/functions, they are included in the norm check, and you will receive a 0 if there is a norm error.
- Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc.) except for undefined behavior. If this occurs, your project will be considered non-functional and will receive a 0 during the evaluation.
- All heap-allocated memory must be properly freed when necessary. Memory leaks will not be tolerated.
- If the subject requires it, you must submit a Makefile that compiles your source files to the required output with the flags -Wall, -Wextra, and -Werror, using cc. Additionally, your Makefile must not perform unnecessary relinking.
- Your Makefile must contain at least the rules $(NAME), all, clean, fclean and re.
- To submit bonuses for your project, you must include a bonus rule in your Makefile, which will add all the various headers, libraries, or functions that are not allowed in the main part of the project. Bonuses must be placed in _bonus.{c/h} files, unless the subject specifies otherwise. The evaluation of mandatory and bonus parts is conducted separately.
- If your project allows you to use your libft, you must copy its sources and its associated Makefile into a libft folder. Your project’s Makefile must compile the library by using its Makefile, then compile the project.
- We encourage you to create test programs for your project, even though this work does not need to be submitted and will not be graded. It will give you an opportunity to easily test your work and your peers’ work. You will find these tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to the assigned Git repository. Only the work in the Git repository will be graded. If Deepthought is assigned to grade your work, it will occur after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.

# V Mandatory part

## V.1 The rules

- You have 2 `stacks` named `a` and `b`.
- At the beginning:
◦ The `stack a` contains a random number of unique negative and/or positive integers.
◦ The `stack b` is empty.
- The goal is to sort the numbers in stack a in ascending order. To achieve this, you
have the following operations at your disposal:
    
    `sa (swap a)`: Swap the first 2 elements at the top of `stack a`.
    Do nothing if there is only one element or none.
    
    `sb (swap b)`: Swap the first 2 elements at the top of `stack b`. Do nothing if there is only one element or none.
    `ss` : `sa` and `sb` at the same time.
    
    `pa (push a)`: Take the first element at the top of `b` and put it at the top of `a`. 
    Do nothing if `b` is empty.
    
    `pb (push b)`: Take the first element at the top of `a` and put it at the top of `b`.
    Do nothing if `a` is empty.
    
    `ra (rotate a)`: Shift up all elements of `stack a` by 1.
    The first element becomes the last one.
    
    `rb (rotate b)`: Shift up all elements of `stack b` by 1.
    The first element becomes the last one.
    
    `rr` : `ra` and `rb` at the same time.
    
    `rra (reverse rotate a)`: Shift down all elements of `stack a` by 1.
    The last element becomes the first one.
    
    `rrb (reverse rotate b)`: Shift down all elements of `stack b` by 1.
    The last element becomes the first one.
    
    `rrr` : `rra` and `rrb` at the same time.
    

## V.2 Example

To illustrate the effect of some of these instructions, let’s sort a random list of integers.
In this example, we’ll consider that both stacks grow from the right.

```
----------------------------------------------------------------------
Init a and b:
2
1
3
6
5
8
_ _
a b
----------------------------------------------------------------------
Exec sa:
1
2
3
6
5
8
_ _
a b
----------------------------------------------------------------------
Exec pb pb pb:
6 3
5 2
8 1
_ _
a b
----------------------------------------------------------------------
Exec ra rb (equiv. to rr):
5 2
8 1
6 3
_ _
a b
----------------------------------------------------------------------
Exec rra rrb (equiv. to rrr):
6 3
5 2
8 1
_ _
a b
----------------------------------------------------------------------
Exec sa:
5 3
6 2
8 1
_ _
a b
----------------------------------------------------------------------
Exec pa pa pa:
1
2
3
5
6
8
_ _
a b
----------------------------------------------------------------------
```

The integers in stack a get sorted in 12 instructions. Can you do better?

## V.3 The "push_swap" program

Program name : push_swap

Turn in files : Makefile, *.h, *.c

Makefile : NAME, all, clean, fclean, re

Arguments 
`stack a` : A list of integers

External functs.
• read, write, malloc, free, exit
• ft_printf or any equivalent YOU coded

Libft authorized : Yes

Description : Sort stacks

Your project must comply with the following rules:

• You have to turn in a `Makefile` which will compile your source files. It must not relink.

• Global variables are forbidden.

• You have to write a program named `push_swap` that takes as an argument the `stack a` formatted as a list of integers. The first argument should be at the top of the stack (be careful about the order).

• The program must display the shortest sequence of instructions needed to sort stack a with the smallest number at the top. 

• Instructions must be separated by a ’`\n`’ and nothing else.

• The goal is to sort the stack with the lowest possible number of operations. During the evaluation process, the number of instructions found by your program will be compared against a limit: the maximum number of operations tolerated. If your program either displays a longer list or if the numbers aren’t sorted properly, your grade will be 0.

• If no parameters are specified, the program must not display anything and should return to the prompt.

• In case of error, it must display "`Error`" followed by an ’`\n`’ on the standard error. Errors include, for example: some arguments not being integers, some arguments exceeding the integer limits, and/or the presence of duplicates.

```bash
$>./push_swap 2 1 3 6 5 8
sa
pb
pb
pb
sa
pa
pa
pa
$>./push_swap 0 one 2 3
Error
$>
```

During the evaluation process, a binary will be provided in order to properly check your program.

It will work as follows:

```bash
$>ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
6
$>ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
OK
$>
```

If the program `checker_OS` displays `"KO"`, it means that your `push_swap` came up with a list of instructions that doesn’t sort the numbers.

ℹ️ The checker_OS program is available in the resources of the project in the intranet.
You can find a description of how it works in the Bonus Part of this document.

## V.4 Benchmark

To validate this project, you must perform certain sorts with a minimal number of operations:

• For maximum project validation (100%) and eligibility for bonuses, you must: 

◦ Sort 100 random numbers in fewer than 700 operations.

◦ Sort 500 random numbers in no more than 5500 operations.

• For minimal project validation (which implies a minimum grade of 80%), you can succeed with different averages:

◦ 100 numbers in under 1100 operations and 500 numbers in under 8500 operations 

◦ 100 numbers in under 700 operations and 500 numbers in under 11500 operations

◦ 100 numbers in under 1300 operations and 500 numbers in under 5500 operations 

...

All of this will be verified during your evaluation.

ℹ️ If you wish to complete the bonus part, you must thoroughly validate the project with each benchmark step achieving the highest possible score.

# VI Bonus part

Due to its simplicity, this project offers limited opportunities for additional features. However, why not create your own checker?

ℹ️ Thanks to the checker program, you will be able to check whether the list of instructions generated by the push_swap program actually sorts the stack properly.

❗ The bonus part will only be assessed if the mandatory part is perfect. Perfect means the mandatory part has been fully completed and functions without errors. In this project, this entails validating all benchmarks without exception. If you have not passed ALL the mandatory requirements,b your bonus part will not be evaluated at all.

## VI.1 The "checker" program

Program name : checker

Turn in files : *.h, *.c

Makefile : bonus

Arguments 
stack a: A list of integers

External functs.
• read, write, malloc, free, exit
• ft_printf or any equivalent YOU coded

Libft authorized : Yes

Description : Execute the sorting instructions

• Write a program named checker that takes as an argument the stack a formatted as a list of integers. The first argument should be at the top of the stack (be careful about the order). If no argument is given, it stops and displays nothing.

• It will then wait and read instructions from the standard input, with each instruction followed by ’\n’. Once all the instructions have been read, the program has to execute them on the stack received as an argument.

• If after executing those instructions, the stack a is actually sorted and the stack b is empty, then the program must display "OK" followed by a ’\n’ on the standard output.

• In every other case, it must display "KO" followed by a ’\n’ on the standard output.

• In case of error, you must display "Error" followed by a ’\n’ on the standard error. Errors include for example: some arguments are not integers, some arguments are bigger than an integer, there are duplicates, an instruction doesn’t exist and/or is incorrectly formatted.

```bash
$>./checker 3 2 1 0
rra
pb
sa
rra
pa
OK
$>./checker 3 2 1 0
sa
rra
pb
KO
$>./checker 3 2 one 0
Error
$>./checker "" 1
Error
$>
```

❗ You DO NOT have to reproduce the exact same behavior as the provided binary. It is mandatory to manage errors but it is up to you to decide how you want to parse the arguments.

# VII Submission and peer-evaluation

Submit your assignment in your Git repository as usual. Only the work inside your repository will be evaluated during the defense. Don’t hesitate to double check the names of your files to ensure they are correct.

As these assignments are not verified by a program, feel free to organize your files as you wish, as long as you turn in the mandatory files and comply with the requirements.
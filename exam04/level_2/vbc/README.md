# VBC (Math Expression Parser using AST)

수학 수식을 파싱하여 **추상 구문 트리(AST, Abstract Syntax Tree)**를 구축하고, 이를 통해 결과값을 계산하는 프로그램입니다. 연산자 우선순위와 재귀적 구조를 이해하는 데 중점을 둡니다.

## 📌 개요

* **목표**: `+`, `*`, `()`가 포함된 한 자리 정수 수식을 계산한다.
* **제약 사항**: 공백 없음, 피연산자는 0~9 사이의 정수.
* **핵심 기술**: 재귀 하강 파싱(Recursive Descent Parsing), AST(Abstract Syntax Tree) 순회.

---

## 🏗️ 데이터 구조 (AST)

수식을 계산하기 위해 각 요소를 노드(Node) 형태로 저장합니다. 연산자 우선순위에 따라 계산 순서가 빠른 노드가 트리의 아래쪽에 배치됩니다.

```c
typedef struct node {
    enum { ADD, MULTI, VAL } type;
    int val;            // VAL 타입일 때만 사용
    struct node *l;     // 왼쪽 자식
    struct node *r;     // 오른쪽 자식
} node;

```

---

## 🧠 파싱 알고리즘 (Recursive Descent)

우선순위가 낮은 연산자 함수가 우선순위가 높은 연산자 함수를 호출하는 방식으로 계층을 나눕니다.

### 문법 계층 구조 (Grammar Hierarchy)

| 함수명 | 처리 연산 | 우선순위 | 동작 설명 |
| --- | --- | --- | --- |
| **`parse_expr`** | **덧셈 (+)** | 낮음 | 전체 수식의 시작점. `term`들을 `+`로 연결합니다. |
| **`term`** | **곱셈 (*)** | 중간 | `factor`들을 `*`로 연결합니다. |
| **`factor`** | **숫자 / ( )** | 높음 | 숫자 노드를 만들거나, `(` 발견 시 `expr`을 재귀 호출합니다. |

---

## 🛠️ 주요 함수 구현 포인트

### 1. 연산자 결합 (Left-associative)

`while` 루프를 사용하여 동일한 우선순위의 연산자가 반복될 때 트리를 왼쪽에서 오른쪽으로 쌓아 올립니다.

```c
node *expr(char **s) {
    node *ret = term(s);
    while (accept(s, '+')) {
        node *right = term(s);
        ret = new_node((node){ADD, 0, ret, right});
    }
    return ret;
}

```

### 2. 괄호와 재귀

`factor`에서 괄호를 만나면 다시 가장 낮은 단계인 `expr`을 호출하여 괄호 내부를 별도의 독립된 수식처럼 처리합니다.

### 3. 에러 전파 (The Return Chain)

허용 함수에 `exit`가 없으므로, 모든 에러(할당 실패, 문법 오류)는 `NULL` 반환을 통해 상위 함수로 전달되어 `main`에서 종료되도록 설계합니다.

---

## ⚠️ 주의사항 (Pitfalls)

* **`accept` 함수 버그 수정**: 제공된 코드의 `if (**s = c)`는 반드시 `if (**s == c)`로 수정해야 합니다. (대입 연산자 실수 주의)
* **포인터 관리**: `char **s`를 통해 문자열의 현재 읽기 위치를 모든 함수가 공유해야 합니다.
* **메모리 누수**: 에러 리턴 시 `destroy_tree`를 호출하여 이미 생성된 노드들을 반드시 해제해야 합니다.
* **끝처리 확인**: `parse_expr`에서 수식이 끝난 후 문자열 포인터가 `\0`인지 확인하여 `1+2)`와 같은 에러를 잡아냅니다.

---

## 🚀 사용법

### 컴파일

```bash
gcc -Wall -Wextra -Werror vbc.c -o vbc

```

### 실행 예시

```bash
$> ./vbc "(3+4)*5"
35
$> ./vbc "1+2*3"
7
$> ./vbc "1+"
Unexpected end of input

```

---

## 📂 파일 구성

* `vbc.h`: 구조체 정의 및 모든 함수 프로토타입 선언 (순환 참조 방지).
* `vbc.c`: 파싱 로직, 트리 계산(`eval_tree`), 메모리 관리 및 메인 함수.

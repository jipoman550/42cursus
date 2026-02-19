# 🚀 Exam04: argo (Tiny JSON Parser)

## 📌 개요

`argo`는 표준 입출력과 동적 메모리 할당을 사용하여 **초소형 JSON 파서(Parser)**를 구현하는 과제입니다. 문자열, 정수, 그리고 중첩 가능한 맵(Map) 구조를 분석하여 메모리 상의 **AST(Abstract Syntax Tree)**로 변환하는 것이 목표입니다.

## 🛠 핵심 데이터 구조: Tagged Union

이 과제의 핵심은 하나의 구조체로 여러 타입을 표현하는 **Tagged Union** 기법입니다.

```c
typedef struct  json {
	enum { MAP, INTEGER, STRING } type;	// 데이터 타입을 식별하는 'Tag'
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;					// MAP 타입일 때 사용
		int		integer;		// INTEGER 타입일 때 사용
		char	*string;		// STRING 타입일 때 사용
	};
} json;

typedef struct  pair {
	char	*key;     // Map의 Key (문자열)
	json	value;    // Map의 Value (재귀적 구조)
} pair;

```

---

## 🏗 구현 로직: Recursive Descent Parser

이 프로그램은 **재귀 하강 파서** 모델을 따릅니다.

### 1. Dispatcher (`argo`)

`peek()` 함수를 통해 스트림의 첫 글자를 확인하고 적절한 파서로 분기합니다.

* `isdigit` 또는 `-` → **Integer Parsing** (`fscanf` 활용)
* `"` → **String Parsing**
* `{` → **Map Parsing** (재귀의 시작)

### 2. String Parser (`parse_string`)

* `realloc`을 사용하여 문자를 읽을 때마다 메모리 크기를 동적으로 확장합니다.
* **Escape Handling:** `\"`와 `\\`만 처리하며, 나머지는 일반 문자로 취급하거나 에러 처리합니다.
* 마지막에 항상 `\0` (NULL terminator)를 붙여 C-style 문자열을 완성합니다.

### 3. Map Parser (`parse_map`)

* **재귀 호출:** Value를 파싱할 때 다시 `argo()`를 호출함으로써 중첩된 JSON 구조를 처리합니다.
* **메모리 확장:** `realloc`으로 `pair` 배열의 크기를 요소 개수만큼 늘려가며 저장합니다.
* **문법 체크:** `{`, `:`, `,`, `}`의 존재 여부를 `expect`와 `accept` 함수로 엄격히 체크합니다.

---

## ⚠️ 주의사항 및 학습 포인트

* **No Spaces:** 표준 JSON과 달리 **공백을 허용하지 않습니다.** 공백 발견 시 `unexpected token` 에러를 발생시켜야 합니다.
* **Error Messages:**
* 예상치 못한 문자: `unexpected token '%c'\n`
* 갑작스러운 종료: `unexpected end of input\n`


* **Memory Management:** * `parse_map`과 `parse_string`에서 발생하는 모든 동적 할당은 실패 시 `-1`을 반환해야 합니다.
* 프로그램 종료 시 `free_json`을 통해 모든 계층의 메모리를 해제해야 `definitely lost` 누수를 막을 수 있습니다.



---

## 🧪 테스트 방법

```bash
# 컴파일
gcc -Wall -Wextra -Werror argo.c -o argo

# 정수 테스트
echo -n '42' | ./argo /dev/stdin | cat -e

# 맵 및 이스케이프 테스트
echo -n '{"key":"value with \"escape\""}' | ./argo /dev/stdin | cat -e

# 메모리 누수 체크
echo -n '{"a":1,"b":{"c":3}}' | valgrind ./argo /dev/stdin

```
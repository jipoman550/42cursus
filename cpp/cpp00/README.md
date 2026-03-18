# C++ - Module 00
**Namespaces, classes, member functions, stdio streams, initialization lists, static, const, and more.**

## 📝 Introduction
이 프로젝트는 **객체지향 프로그래밍(Object-Oriented Programming, OOP)**의 기본 개념을 익히기 위한 C++ 여정의 시작점입니다.  익숙한 C언어를 넘어 C++98 표준을 따르며 새로운 개념들을 단계별로 학습합니다.

## 🛠️ General Rules
과제를 수행하며 반드시 준수해야 하는 엄격한 규칙들입니다.

### 1. Compilation
* **Compiler**: `c++`
* **Flags**: `-Wall -Wextra -Werror`
* **Standard**: `-std=c++98` 플래그를 추가해도 컴파일에 문제가 없어야 합니다.

### 2. Naming Conventions
* **Directories**: `ex00`, `ex01`, ..., `exn`
* **Class Names**: **UpperCamelCase** 형식을 따릅니다.
* **Files**: 헤더 파일과 소스 파일명은 반드시 클래스 이름과 일치해야 합니다. (예: `ClassName.hpp`, `ClassName.cpp`)

### 3. Forbidden & Allowed
* **Forbidden Functions**: `*printf()`, `*alloc()`, `free()` 사용은 절대 금지됩니다. (위반 시 0점)
* **Forbidden Keywords**: 명시적인 허용 없이는 `using namespace <ns_name>`과 `friend` 키워드를 사용할 수 없습니다. (위반 시 **-42점**)
* **STL Restricted**: Module 08 전까지 컨테이너(vector, list, map 등)와 알고리즘 헤더 사용이 금지됩니다. (위반 시 **-42점**)
* **Header Files**: 템플릿이 아닌 함수 구현을 헤더에 넣는 행위는 금지되며, 반드시 **Include Guard**를 포함해야 합니다.

---

## 🔊 Exercise 00: Megaphone
표준 입출력 스트림(`iostream`)과 문자열 처리를 연습하는 단계입니다.

### Objectives
* 입력받은 문자열 인자들을 모두 대문자로 변환하여 출력합니다.
* 입력 인자가 없을 경우, 사전에 정의된 특정 소음 메시지를 출력합니다.

### Key Concepts
* **`std::cout` & `std::endl`**: C의 `printf`를 대체하는 C++ 스타일의 입출력.
* **`std::toupper`**: 문자를 대문자로 변환하는 방식 이해.
* **Namespace `std`**: `using namespace` 없이 `std::` 접두사를 명시적으로 사용하는 습관.

### Usage
```bash
$ make
$ ./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
$ ./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
$ ./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

---

## 📁 Directory Structure
* `ex00/`: Megaphone 프로그램 및 Makefile.
* `ex01/`: My Awesome PhoneBook (진행 예정).
* `ex02/`: The Job Of Your Dreams (진행 예정).


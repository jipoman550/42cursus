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

// for 문 문법 정리

// std::cout, std::endl, std::toupper 정리

---

제공해주신 `README_kor.md` 파일의 형식에 맞춰, 우리가 대화하며 구현한 `ex01: My Awesome PhoneBook`의 내용을 정리했습니다. 아래 내용을 그대로 복사하여 `README_kor.md`의 `Exercise 00` 뒷부분에 붙여넣으시면 됩니다.

---

## 📖 Exercise 01: My Awesome PhoneBook
80년대 스타일의 투박하지만 멋진 전화번호부 소프트웨어를 구현하는 단계입니다. 클래스의 설계, 객체의 생명주기(생성자와 소멸자), 그리고 표준 입출력 제어를 심도 있게 다룹니다.

### Objectives
* **최대 8개의 연락처 저장**: 연락처는 최대 8개까지 저장 가능하며, 9번째부터는 가장 오래된 연락처를 새로운 정보로 덮어씁니다(Circular Buffer 구조).
* **동적 할당 금지**: `new`, `delete` 등 동적 메모리 할당을 사용하지 않고 정적 배열로 구현합니다.
* **명령어 처리**: 프로그램은 `ADD`, `SEARCH`, `EXIT` 세 가지 명령어를 입력받아 수행합니다.

### Class Structure
* **`Contact` 클래스**: 개별 연락처 정보를 담는 단위입니다.
    * 이름, 성, 별명, 전화번호, 어두운 비밀을 저장합니다.
    * 데이터 보호를 위해 속성(Attributes)은 `private`으로, 기능(Functions)은 `public`으로 설계합니다.
* **`PhoneBook` 클래스**: `Contact` 객체들의 배열을 관리하며 전체 시스템을 제어합니다.

### Key Features
* **`ADD`**: 사용자가 필드별로 정보를 입력하며, 빈 칸 입력 시 다시 입력을 요구하여 데이터 무결성을 유지합니다.
* **`SEARCH`**: 저장된 목록을 인덱스, 이름, 성, 별명 순으로 10자 너비의 표 형식으로 출력합니다.
    * 10자가 넘는 문자열은 9자만 출력하고 마지막에 마침표(`.`)를 찍어 형식을 맞춥니다.
    * 목록 출력 후 특정 인덱스를 선택하면 해당 연락처의 모든 정보를 상세히 보여줍니다.
* **`EXIT`**: 프로그램을 종료하며 저장된 모든 연락처 정보는 영구히 삭제됩니다.

### Key Concepts (Lessons Learned)
* **생성자 & 소멸자**: 객체가 생성될 때 변수를 초기화하고, 소멸될 때 뒷정리를 수행하는 특별한 멤버 함수의 개념을 익혔습니다.
* **`const` 멤버 함수**: 객체의 내부 데이터를 수정하지 않고 읽기만 하는 함수에 `const`를 붙여 코드의 안전성과 신뢰성을 높였습니다.
* **`std::setw` & `std::right`**: `<iomanip>` 헤더를 사용하여 텍스트 정렬 및 고정된 열 너비를 출력하는 포맷팅 기법을 학습했습니다.
* **객체(Object)와 인스턴스(Instance)**: 클래스라는 설계도를 바탕으로 실제 메모리에 생성된 실체들 간의 관계를 이해했습니다.

### Usage
```bash
$ make
$ ./phonebook
Welcome to My Awesome PhoneBook!
Enter command (ADD, SEARCH, EXIT): ADD
Enter First Name: Bjarne
Enter Last Name: Stroustrup
...
Successfully added!
Enter command (ADD, SEARCH, EXIT): SEARCH
|     index|first name| last name|  nickname|
|         0|    Bjarne|Stroustrup|    cpp_god|
Enter index to display details: 0
First Name     : Bjarne
Last Name      : Stroustrup
...
Enter command (ADD, SEARCH, EXIT): EXIT
The program quits and the contacts are lost forever!
```

---

## 📁 Directory Structure Update
* `ex00/`: Megaphone 프로그램 및 Makefile.
* `ex01/`: My Awesome PhoneBook 프로그램 (클래스 기반 구현).
* `ex02/`: The Job Of Your Dreams (진행 예정).



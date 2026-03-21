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

### 💡 Deep Dive: Megaphone 핵심 Q&A

#### **Q1. 왜 `printf` 대신 `std::cout`을 사용했나요?**
* **답변**: C++의 표준 출력 스트림인 `std::cout`은 **타입 안전성(Type-safe)**을 보장합니다. `printf`와 달리 서식 지정자(`%d`, `%s` 등)를 잘못 써서 발생하는 런타임 오류를 방지할 수 있으며, `<<` 연산자 오버로딩을 통해 다양한 데이터 타입을 유연하게 출력할 수 있기 때문입니다.

#### **Q2. 네임스페이스(Namespace)란 무엇이며, 왜 `std::`를 붙여야 하나요?**
* **답변**: 네임스페이스는 식별자(함수, 클래스 등)의 **이름 충돌을 방지**하기 위한 논리적인 공간입니다. `std`는 C++ 표준 라이브러리의 모든 기능이 담긴 네임스페이스이며, `std::`를 명시함으로써 해당 식별자가 표준 라이브러리 소속임을 명확히 하고 다른 라이브러리와의 이름 중복 문제를 해결합니다.

#### **Q3. `std::endl`과 `\n`의 차이는 무엇인가요?**
* **답변**: `\n`은 단순히 줄바꿈 문자만을 출력하지만, `std::endl`은 **줄바꿈과 동시에 출력 버퍼를 강제로 비우는(flush)** 작업까지 수행합니다. 따라서 실시간으로 출력을 확인해야 하는 상황에서는 `std::endl`이 유리하지만, 대량의 데이터를 출력할 때는 성능을 위해 `\n`을 사용하는 것이 더 효율적일 수 있습니다.

### 🔍 C++ Basic Syntax

#### **For Loop Structure**
`for (initialization; condition; increment)`
1. **initialization**: 루프 시작 시 1회 실행 (변수 초기화).
2. **condition**: 매 루프 시작 전 평가 (true일 때만 실행).
3. **increment**: 본문 실행 후 수행 (변수 값 업데이트).

#### **Standard Library (std::)**
- **`std::cout`**: 표준 출력 스트림 객체 (Type-safe 출력).
- **`std::endl`**: 줄바꿈 + 출력 버퍼 비우기(flush).
- **`std::toupper`**: 문자를 대문자로 변환하는 함수.

#### **Safe Truncation & Casting**
- **`(unsigned char)`**: `std::toupper`는 음수 입력 시 정의되지 않은 동작을 일으킬 수 있음. `char`가 signed일 경우를 대비해 양수 범위(`unsigned char`)로 안전하게 변환하여 전달함.
- **`(char)`**: `std::toupper`의 반환형인 `int`를 다시 문자 포맷으로 출력하기 위해 변환함.

#### **Operator Overloading (연산자 오버로딩)**
- **정의**: 기존 연산자(`+`, `-`, `<<` 등)를 특정 클래스나 타입에 맞게 재정의하는 기능.
- **std::cout과 <<**: 비트 시프트 연산자였던 `<<`를 '출력 스트림 삽입 연산자'로 재정의함.
- **장점**:
  1. **자동 타입 인식**: 데이터 타입을 컴파일러가 판단하여 적절한 오버로딩 함수를 호출.
  2. **가독성**: 서식 지정자 없이도 직관적인 코드 작성이 가능함.

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

### 📚 공부한 기록 및 핵심 개념

#### 1. 객체지향 설계 (OOP Design)

* **클래스 분리의 이유 (`Contact` vs `PhoneBook`)**:
	* **역할과 책임의 분리(Separation of Concerns)**: `Contact`는 개별 정보를 저장하고 출력하는 책임(명함)을, `PhoneBook`은 연락처 배열을 관리하고 순환 로직을 제어하는 책임(명함첩)을 갖도록 설계했습니다.
	* **캡슐화와 데이터 보호**: 정보를 `private`에 숨김으로써 데이터가 뒤섞이거나 외부에서 임의로 수정되는 것을 방지하고, 허용된 방식(`public` 함수)으로만 소통하게 하여 안정성을 높였습니다.
* **멤버 변수 명명 규칙 (`_`)**:
	* 멤버 변수 앞에 언더바(`_`)를 붙여 매개변수나 지역 변수와 시각적으로 즉시 구분되도록 했습니다. (예: `_firstName = firstName`)
	* **주의**: 시스템 예약어와의 충돌을 피하기 위해 `_FirstName`(언더바+대문자)이 아닌 `_firstName`(언더바+소문자) 형식을 사용했습니다.

#### 2. C++ 핵심 문법
* **생성자(Constructor)와 소멸자(Destructor)**:
	* **생성자**: 객체가 메모리에 생성될 때 자동 호출되어 변수를 초기화합니다.
	* **소멸자**: 객체의 수명이 다할 때 호출되며, 이번 과제에서는 동적 할당을 사용하지 않으므로 기본적인 형태만 갖추었습니다.
* **`const` 멤버 함수**:
	* 함수 선언 뒤에 `const`를 붙여 해당 함수가 객체의 상태(멤버 변수)를 절대 바꾸지 않는 '읽기 전용'임을 보장했습니다.
	* 이는 의도치 않은 데이터 수정을 방지하며, 상수 객체에서도 해당 함수를 호출할 수 있게 합니다.
* **클래스 vs 객체 vs 인스턴스**:
	* **클래스**: 붕어빵 틀(설계도).
	* **객체(Object)**: 메모리에 할당된 실체.
	* **인스턴스(Instance)**: 특정 클래스로부터 태어났다는 '관계'를 강조할 때 사용하는 용어입니다.

#### 3. 구현 디테일
* **순환 저장 로직 (Circular Buffer)**:
	* 별도의 삭제 로직 없이 `% 8` (Modulo 연산)을 활용하여 인덱스가 8을 넘어가면 자동으로 0번부터 다시 덮어쓰도록 구현했습니다.
* **텍스트 포맷팅**:
	* `<iomanip>`의 `std::setw(10)`과 `std::right`를 사용하여 10자 너비의 오른쪽 정렬 표 형식을 맞추고, 10자 초과 시 9자만 출력 후 `.`을 붙이는 로직을 적용했습니다.

### 💬 Evaluation FAQ (평가 대비 질문)

**Q: 왜 `std::cin >>` 대신 `std::getline`을 사용했나요?**
* **A**: `std::cin >>`은 공백(스페이스, 탭)을 만나면 입력을 중단하지만, `std::getline`은 줄바꿈 문자(`\n`)를 만날 때까지의 전체 문장을 입력받습니다. 이름이나 별명에 공백이 포함될 수 있는 전화번호부 특성상 데이터 누락 방지를 위해 `std::getline`을 사용했습니다.

**Q: 인덱스 순환 처리를 어떻게 보장했나요?**
* **A**: 전체 입력 횟수를 관리하는 변수를 배열 크기인 8로 나눈 나머지(`_totalCount % 8`)를 인덱스로 사용하여, 9번째 입력이 들어오면 자동으로 0번 인덱스를 가리키도록 설계했습니다.

**Q: 입력 도중 `Ctrl+D`(EOF)가 들어올 경우 어떻게 처리했나요?**
* **A**: `std::getline`은 EOF를 만나면 `false`를 반환합니다. 이를 조건문으로 체크하여 프로그램이 무한 루프에 빠지지 않고 안전하게 입력을 중단하거나 종료되도록 방어 코딩을 적용했습니다.

**Q: `using namespace std;`를 사용하지 않은 이유는 무엇인가요?**
* **A**: 대규모 프로젝트에서 이름 충돌(Naming Collision)을 방지하기 위함입니다. 어떤 도구가 표준 라이브러리(`std`)에서 왔는지 명시적으로 밝히는 습관을 들이고 이름 공간을 오염시키지 않기 위해 매번 `std::`를 명시했습니다.

---

## 🏦 Exercise 02: The Job Of Your Dreams
이 과제는 주어진 설계도(`Account.hpp`)와 테스트 결과물(로그 파일)을 바탕으로 실제 동작하는 로직을 복원하는 **리버스 엔지니어링(Reverse Engineering)** 단계입니다.

### Objectives
* **`Account.cpp` 복원**: 제공된 `Account.hpp`와 `tests.cpp`를 수정하지 않고, 로그 파일(`19920104_091532.log`)과 동일한 출력을 생성하는 소스 코드를 작성합니다.
* **은행 시스템 로직 구현**: 개별 계좌의 입출금뿐만 아니라, 모든 계좌를 아우르는 은행 전체의 통계(총 잔액, 총 입출금 횟수 등)를 실시간으로 관리합니다.

### Key Features
* **정적(Static) 멤버 관리**: 모든 객체가 공유하는 은행 전체 데이터를 처리하기 위해 `static` 변수와 함수를 활용합니다.
* **타임스탬프 출력**: `_displayTimestamp` 함수를 통해 로그의 모든 줄 시작 부분에 `[YYYYMMDD_HHMMSS]` 형식의 현재 시간을 출력합니다.
* **입출금 유효성 검사**: 출금 시 잔액이 부족하면 `refused` 메시지를 출력하고 트랜잭션을 거부하는 예외 처리 로직을 포함합니다.

### Key Concepts (Lessons Learned)
* **`static` 멤버 변수 & 함수**: 클래스 인스턴스가 아닌 클래스 자체에 귀속되는 데이터와 기능을 정의하고, `.cpp` 파일에서 이를 초기화하는 방법을 익혔습니다.
* **멤버 초기화 리스트 (Member Initializer List)**: 생성자 본체가 실행되기 전에 멤버 변수를 효율적으로 초기화하는 문법(`: variable(value)`)을 학습했습니다.
* **캡슐화와 Getter**: `private` 데이터를 안전하게 읽기 위한 `get...()` 및 `check...()` 함수(Getter)의 역할과 중요성을 이해했습니다.
* **`const` Correctness**: 객체의 상태를 변경하지 않는 함수에 `const`를 명시하여 코드의 안정성을 확보하는 습관을 들였습니다.

### Usage & Testing
```bash
# 컴파일 및 실행
$ make
$ ./account > my_log.log

# 타임스탬프를 제외한 로직 결과 비교 (리눅스/맥 기준)
$ diff <(sed 's/\[[^]]*\] //' my_log.log) <(sed 's/\[[^]]*\] //' 19920104_091532.log)

$ diff <(cut -d ' ' -f2- my_log.log) <(cut -d ' ' -f2- 19920104_091532.log)
# 결과가 아무것도 출력되지 않으면 로그 매칭 성공!
```

### 📚 공부한 기록 및 핵심 개념


#### 1. **정적 멤버 변수 (Static Member Variables)**
- **공유성**: 특정 객체가 아닌 클래스 자체에 귀속되며, 모든 인스턴스가 동일한 메모리 공간을 공유함.
- **생명 주기**: 프로그램 시작 시 할당, 종료 시 소멸 (Data Segment 영역).
- **초기화 위치**: 반드시 `.cpp` 파일에서 수행.
  - 이유: 헤더 파일 초기화 시 중복 정의(Duplicate Definition) 에러 발생 방지.
- **캡슐화**: 전역 변수와 수명은 같지만, 클래스 내부에 선언되어 무분별한 접근을 막을 수 있음.

카뎃, 정적 멤버 변수에 이어 **정적 멤버 함수**와 **C/C++의 `static` 차이점**을 옵시디언이나 `README.md`에 바로 붙여넣기 좋게 정리해 드릴게요.

이 내용은 특히 `ex02` 평가 때 "이 함수는 왜 `static`인가요?"라는 질문에 방어하기 딱 좋은 논리들입니다.


#### 2. **정적 멤버 함수 (Static Member Function)**

- **객체 독립성**: 특정 인스턴스가 아닌 **클래스 자체에 귀속**되는 함수입니다. 객체를 단 하나도 생성하지 않아도 `Account::getNbAccounts()`처럼 호출할 수 있습니다.
- **`this` 포인터의 부재**: 일반 멤버 함수와 달리 호출 시 객체의 주소(`this`)가 전달되지 않습니다.
- **접근 제한**: `this`가 없기 때문에 어떤 객체의 데이터인지 알 수 없는 **일반 멤버 변수(인스턴스 변수)에는 접근할 수 없으며**, 오직 정적 멤버 변수만 다룰 수 있습니다.
- **사용 이유**:
	- 개별 객체의 상태와 무관한 '클래스 전체의 통계'나 '유틸리티 기능'을 수행하기 위해 사용합니다.
	- 불필요한 객체 생성 없이 함수를 호출하여 메모리와 성능을 최적화합니다.


#### 3. **`static` 키워드의 두 얼굴: C vs C++**

C++은 C언어의 `static` 특성을 계승하면서도, '클래스'라는 개념에 맞춰 새로운 정의를 추가했습니다.

| 구분 | C언어 (Internal Linkage) | C++ (Class Scope) |
| :--- | :--- | :--- |
| **위치** | 클래스 외부 (전역 범위) | 클래스 내부 |
| **의미** | **파일 단위의 캡슐화** | **객체 단위의 독립성** |
| **효과** | 해당 파일(`.c`/`.cpp`) 외부에서 접근 불가 | 객체 생성 없이 클래스 이름으로 접근 가능 |
| **주요 목적** | 다른 파일과의 이름 충돌 방지 | 모든 인스턴스가 공유하는 로직/데이터 관리 |

- **C-Style Static**: "이 함수/변수는 **이 파일 안에서만** 쓰겠다"는 선언입니다.
- **C++ Class Static**: "이 함수/변수는 **객체와 상관없이 클래스 소속**으로 쓰겠다"는 선언입니다.


#### 4. **정적 멤버 함수를 사용하는 이유 (Why use Static Member Functions?)**

단순히 전역 함수로 만들 수 있음에도 불구하고, 굳이 클래스 내부에 `static` 함수를 선언하여 "객체 없이" 사용하게 만드는 이유는 다음과 같습니다.

1. **논리적 타당성 (Logical Validity)**
	- **객체에게 묻기 어색한 질문 해결**: `ex02`의 은행 시스템에서 "당신의 잔액은 얼마입니까?"는 개별 계좌(객체)에게 물어야 하지만, "현재 전체 계좌 수는 몇 개입니까?"는 특정 계좌가 아닌 **은행 시스템 전체(클래스)**에 물어야 하는 질문입니다.
	- 만약 `static` 함수가 없다면, 전체 정보를 알기 위해 굳이 불필요한 계좌를 하나 개설(객체 생성)해야만 하는 비논리적인 상황이 발생합니다.

2. **자원 효율성 (Resource Efficiency)**
	- **불필요한 인스턴스화 방지**: 함수 하나를 쓰기 위해 메모리를 할당하고 생성자를 호출하여 객체를 만드는 것은 낭비입니다. `static` 함수를 쓰면 객체 생성 없이 함수만 바로 호출할 수 있어 메모리와 성능을 최적화할 수 있습니다.

3. **구조적 관리 및 이름 공간(Namespace) 정리**
	- **관련 기능의 그룹화**: 전역 함수로 만들면 나중에 다른 라이브러리와 이름이 충돌할 위험이 큽니다. 하지만 `Account::displayTimestamp()`처럼 클래스 내부에 두면 이 함수가 어떤 클래스와 관련 있는지 명확해지며, **캡슐화**를 유지하면서 이름 충돌도 방지할 수 있습니다. (클래스를 일종의 '이름 주머니'로 활용)


#### 5. **생성자와 소멸자의 역할 (Constructor & Destructor)**

객체의 탄생과 죽음은 개별 객체의 상태 변화뿐만 아니라, 클래스 전체의 공유 데이터(Static)에도 영향을 미칩니다.

1. **생성자 (Constructor): 객체의 탄생과 시스템 등록**
	- **개별 초기화**: 각 계좌(객체)가 가질 고유한 인덱스(`_accountIndex`)와 초기 잔액(`_amount`)을 설정합니다.
	- **글로벌 통계 업데이트**: 새로운 계좌가 생성될 때마다 전체 계좌 수(`_nbAccounts`)를 증가시키고, 초기 입금액을 전체 예치금(`_totalAmount`)에 합산합니다.
	- **ID 부여 로직**: `_accountIndex(_nbAccounts)`를 먼저 수행한 후 `_nbAccounts++`를 함으로써, 0번부터 순차적인 고유 ID를 부여하는 설계를 적용했습니다.

2. **소멸자 (Destructor): 객체의 소멸과 마무리**
	- **로그 기록**: 객체가 메모리에서 해제되기 직전, 해당 계좌의 마지막 상태(index, amount)를 출력하여 폐쇄(`closed`)를 기록합니다.
	- **자원 및 통계 정리**: 프로그램의 논리적 완결성을 위해 소멸 시 전체 계좌 수(`_nbAccounts`)를 감소시키거나 남은 잔액을 전체 금액에서 제외하는 등의 처리가 가능합니다. (본 과제에서는 프로그램 종료 시 순차적으로 소멸됨)



#### 6. **멤버 초기화 리스트 (Member Initializer List)**

생성자에서 멤버 변수를 초기화할 때, 생성자 본체(`{ }`) 내부에서 대입하는 대신 **초기화 리스트**를 사용하는 것이 권장됩니다.

- **효율성**: 변수를 생성한 후 값을 대입하는 것이 아니라, **생성과 동시에 초기화**하므로 불필요한 연산을 줄입니다.
- **필수성**: `const` 멤버 변수나 참조자(`&`) 멤버는 반드시 초기화 리스트에서만 초기화할 수 있습니다.
- **실행 순서**: 초기화 리스트에 적힌 순서가 아니라, **클래스 헤더(.hpp)에 멤버 변수가 선언된 순서**대로 초기화가 진행됨에 유의해야 합니다. "만약 한 멤버 변수의 초기화에 다른 멤버 변수가 사용될 경우, 초기화 리스트에 적힌 순서만 믿고 코드를 짰다가 선언 순서가 달라 예상치 못한 쓰레기 값이 들어갈 수 있기 때문입니다.


---

## 📁 Directory Structure Update
* `ex00/`: Megaphone 프로그램 및 Makefile.
* `ex01/`: My Awesome PhoneBook 프로그램.
* `ex02/`: The Job Of Your Dreams (은행 계좌 관리 시스템 복원).

# 📖 C++ - Module 04
**Subtype Polymorphism, Abstract Classes, and Interfaces (다형성, 추상 클래스, 인터페이스)**

## 📝 Introduction
이 프로젝트는 객체지향 프로그래밍(OOP)의 꽃이라 불리는 **다형성(Polymorphism)**을 깊이 있게 다룹니다. 부모 타입의 포인터로 자식 객체를 제어하는 **동적 바인딩(Dynamic Binding)**의 원리를 이해하고, 힙 메모리를 소유한 객체의 **깊은 복사(Deep Copy)**, 그리고 인스턴스화를 제한하는 **추상 클래스(Abstract Class)**와 **인터페이스(Interface)** 설계법을 학습합니다.

## 🛠️ General Rules
과제를 수행하며 반드시 준수해야 하는 규칙들입니다.

### 1. Compilation
* **Compiler**: `c++`
* **Flags**: `-Wall -Wextra -Werror`
* **Standard**: `-std=c++98` 플래그를 추가해도 완벽하게 컴파일되어야 합니다.

### 2. Forbidden & Allowed
* **C 함수 사용 금지**: `printf()`, `malloc()`, `free()` 사용 시 **0점** 처리됩니다.
* **STL 제한**: Module 08 이전까지 컨테이너(`vector`, `list`, `map` 등)와 알고리즘 사용이 금지됩니다.
* **Orthodox Canonical Class Form (OCCF)**: 모든 클래스는 반드시 기본 생성자, 복사 생성자, 복사 대입 연산자, 소멸자를 포함해야 합니다.
* **🚨 Virtual Destructor**: 다형성을 사용하는 상속 구조에서는 부모 클래스의 소멸자를 반드시 `virtual`로 선언하여 자식 객체의 메모리 누수를 방지해야 합니다.

---

## 🐾 Exercise 00: Polymorphism
부모 클래스 `Animal`과 자식 클래스 `Dog`, `Cat`을 통해 기본적인 다형성을 구현합니다.

### Objectives
* `virtual` 키워드를 사용한 `makeSound()` 함수의 동적 바인딩 확인.
* `WrongAnimal` 예시를 통해 `virtual`이 없을 때 발생하는 정적 바인딩 문제 학습.

### 💡 Deep Dive

#### **Q1. `Animal* meta = new Dog();` 에서 `virtual`이 왜 중요한가요?**
* **답변**: `virtual`이 없다면 컴파일러는 포인터 타입인 `Animal`의 함수만 호출합니다(정적 바인딩). `virtual`을 선언해야만 런타임에 실제 가리키는 객체(`Dog`)를 확인하여 자식의 함수를 호출하는 **동적 바인딩**이 일어납니다.

---

## 🧠 Exercise 01: I don't want to set the world on fire
객체가 다른 객체를 포인터로 소유할 때 발생하는 메모리 관리와 복사 문제를 다룹니다.

### Objectives
* 100개의 아이디어를 가진 `Brain` 클래스 구현.
* `Dog`와 `Cat`이 `Brain`을 동적 할당하여 소유하도록 설계.
* **깊은 복사(Deep Copy)**를 통한 독립적인 객체 상태 유지.

### 💡 Deep Dive

#### **Q1. 얕은 복사(Shallow Copy)가 왜 위험한가요?**
* **답변**: 단순히 포인터 주소만 복사하면 두 객체가 하나의 `Brain`을 공유하게 됩니다. 이 경우 한 객체가 소멸하면서 `Brain`을 `delete`하면, 다른 객체는 이미 해제된 메모리를 참조하게 되어 프로그램이 충돌합니다.

#### **Q2. 가상 소멸자가 누락되면 어떤 일이 벌어지나요?**
* **답변**: `Animal*` 포인터로 `Dog`를 `delete`할 때, 부모 소멸자만 호출되고 자식 소멸자가 무시됩니다. 결과적으로 `Dog` 내부의 `Brain`이 해제되지 않아 **메모리 누수**가 발생합니다.

---

## 🚫 Exercise 02: Abstract class
"그냥 동물"은 존재할 수 없다는 논리적 설계를 위해 추상 클래스를 도입합니다.

### Objectives
* `Animal` 클래스를 인스턴스화할 수 없는 **추상 클래스**로 변환.
* **순수 가상 함수(Pure Virtual Function)** 문법 이해.

### 💡 Deep Dive

#### **Q1. 추상 클래스로 만드는 가장 간단한 방법은?**
* **답변**: 함수 선언 뒤에 `= 0;`을 붙여 **순수 가상 함수**로 만드는 것입니다. 이 함수가 하나라도 포함된 클래스는 직접 객체를 생성할 수 없게 됩니다.

---

## 💎 Exercise 03: Interface & recap
C++98에서 인터페이스 개념을 구현하고, 복잡한 객체 생성 시스템을 설계합니다.

### Objectives
* `AMateria`를 기반으로 한 `Ice`, `Cure` 클래스 구현.
* `ICharacter` 인터페이스를 통한 캐릭터 인벤토리 시스템 관리.
* `IMateriaSource`를 통한 마테리아 템플릿 생산(Prototype 패턴 기초).

### 💡 Deep Dive

#### **Q1. `unequip()`에서 마테리아를 `delete`하지 않는 이유는?**
* **답변**: 과제 규칙상 `unequip`은 장착 해제만 수행할 뿐, 마테리아의 소유권 처리는 사용자의 몫으로 남겨둡니다. 메모리 누수를 막기 위해 해제된 마테리아의 주소를 별도로 관리(예: floor 배열)하여 나중에 정리해야 합니다.

#### **Q2. `clone()` 함수는 어떤 역할을 하나요?**
* **답변**: 실제 타입을 모르는 `AMateria*` 상태에서도 자신과 똑같은 타입의 새 객체를 복제하여 반환해 줍니다. 이는 다형성을 유지하며 새로운 인스턴스를 생성하는 강력한 도구가 됩니다.

---

## 📁 Directory Structure
* `ex00/`: 가상 함수와 다형성 기초.
* `ex01/`: 동적 할당 멤버와 깊은 복사.
* `ex02/`: 순수 가상 함수와 추상 클래스.
* `ex03/`: 인터페이스 구현 및 종합 마테리아 시스템.

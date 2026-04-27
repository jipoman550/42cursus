#include "Dog.hpp"

// ────────────────────────────────────────────────────────────
// Dog 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: Animal() 먼저 호출된 뒤, type을 "Dog"로 설정 ──
Dog::Dog()
{
	this->type = "Dog"; // 부모 클래스의 protected 멤버에 직접 접근 가능
	std::cout << "Dog: Calling the default constructor" << std::endl;
}

// ── 복사 생성자: Animal 복사 생성자를 먼저 호출 ──
Dog::Dog(const Dog &other) : Animal(other)
{
	std::cout << "Dog: Calling the copy constructor" << std::endl;
}

// ── 대입 연산자: 부모의 대입 연산자를 명시적으로 호출 ──
Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog: Calling the assignment operator" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other); // 부모 클래스의 대입 연산자 호출
	}
	return (*this);
}

// ── 소멸자 ──
Dog::~Dog()
{
	std::cout << "Dog: Calling the destructor" << std::endl;
}

// ── makeSound(): Dog만의 소리를 출력 (동적 바인딩으로 이 함수가 호출됨) ──
void Dog::makeSound() const
{
	std::cout << "Dog: Woof! Woof! Woof! Woof!" << std::endl;
}

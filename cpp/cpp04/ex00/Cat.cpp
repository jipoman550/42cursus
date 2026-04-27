#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// Cat 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: type을 "Cat"으로 설정 ──
Cat::Cat()
{
	this->type = "Cat";
	std::cout << "Cat: Calling the default constructor" << std::endl;
}

// ── 복사 생성자 ──
Cat::Cat(const Cat &other) : Animal(other)
{
	std::cout << "Cat: Calling the copy constructor" << std::endl;
}

// ── 대입 연산자 ──
Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat: Calling the assignment operator" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
	}
	return (*this);
}

// ── 소멸자 ──
Cat::~Cat()
{
	std::cout << "Cat: Calling the destructor" << std::endl;
}

// ── makeSound(): Cat만의 소리를 출력 ──
void Cat::makeSound() const
{
	std::cout << "Cat: Meow! Meow! Meow! Meow!" << std::endl;
}

#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// Cat 클래스 구현 (Brain을 동적 할당)
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: Brain을 힙에 new로 생성 ──
Cat::Cat()
{
	this->type  = "Cat";
	this->brain = new Brain();
	std::cout << "Cat: Call default constructor (brain assigned)" << std::endl;
}

// ── 복사 생성자: 깊은 복사 ──
Cat::Cat(const Cat &other) : Animal(other)
{
	this->brain = new Brain(*other.brain);
	std::cout << "Cat: Call copy constructor (brain deep copy)" << std::endl;
}

// ── 대입 연산자: 깊은 복사 ──
Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat: Call assignment operator (brain deep copy)" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return (*this);
}

// ── 소멸자: brain 반드시 해제 ──
Cat::~Cat()
{
	delete this->brain;
	std::cout << "Cat: Destructor called (brain released)" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Meow! Meow! Meow! Meow!" << std::endl;
}

Brain *Cat::getBrain() const
{
	return (this->brain);
}

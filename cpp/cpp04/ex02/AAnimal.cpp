#include "AAnimal.hpp"

// ────────────────────────────────────────────────────────────
// AAnimal 추상 클래스 구현
// 순수 가상 함수(makeSound)의 본체는 여기에 없음 → 자식이 구현해야 함
// ────────────────────────────────────────────────────────────

AAnimal::AAnimal() : type("AAnimal")
{
	std::cout << "AAnimal: Calling the default constructor" << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : type(other.type)
{
	std::cout << "AAnimal: Calling the copy constructor" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other)
{
	std::cout << "AAnimal: Calling the assignment operator" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

AAnimal::~AAnimal()
{
	std::cout << "AAnimal: Calling the destructor" << std::endl;
}

std::string AAnimal::getType() const
{
	return (this->type);
}

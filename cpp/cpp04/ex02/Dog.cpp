#include "Dog.hpp"

Dog::Dog()
{
	this->type  = "Dog";
	this->brain = new Brain();
	std::cout << "Dog: Call default constructor" << std::endl;
}

Dog::Dog(const Dog &other) : AAnimal(other)
{
	this->brain = new Brain(*other.brain); // 깊은 복사
	std::cout << "Dog: Call copy constructor" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog: Call assignment operator" << std::endl;
	if (this != &other)
	{
		AAnimal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return (*this);
}

Dog::~Dog()
{
	delete this->brain;
	std::cout << "Dog: Destructor called" << std::endl;
}

// ── 순수 가상 함수 구현: 이게 없으면 Dog도 추상 클래스가 됨 ──
void Dog::makeSound() const
{
	std::cout << "Woof! Woof! Woof! Woof!" << std::endl;
}

Brain *Dog::getBrain() const
{
	return (this->brain);
}

#include "Cat.hpp"

Cat::Cat()
{
	this->type  = "Cat";
	this->brain = new Brain();
	std::cout << "Cat: Call default constructor" << std::endl;
}

Cat::Cat(const Cat &other) : AAnimal(other)
{
	this->brain = new Brain(*other.brain);
	std::cout << "Cat: Call copy constructor" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat: Call assignment operator" << std::endl;
	if (this != &other)
	{
		AAnimal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*other.brain);
	}
	return (*this);
}

Cat::~Cat()
{
	delete this->brain;
	std::cout << "Cat: Destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Meow! Meow! Meow! Meow!" << std::endl;
}

Brain *Cat::getBrain() const
{
	return (this->brain);
}

#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
	std::cout << "Animal: Calling the default constructor" << std::endl;
}

Animal::Animal(const Animal &other) : type(other.type)
{
	std::cout << "Animal: Calling the copy constructor" << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
	std::cout << "Animal: Calling the assignment operator" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal: Calling the destructor" << std::endl;
}

void Animal::makeSound() const
{
	std::cout << "Animal: Animals make sounds." << std::endl;
}

std::string Animal::getType() const
{
	return (this->type);
}

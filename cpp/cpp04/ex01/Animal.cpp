#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
    std::cout << "Animal: 기본 생성자 호출" << std::endl;
}

Animal::Animal(const Animal &other) : type(other.type)
{
    std::cout << "Animal: 복사 생성자 호출" << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
    std::cout << "Animal: 대입 연산자 호출" << std::endl;
    if (this != &other)
        this->type = other.type;
    return (*this);
}

Animal::~Animal()
{
    std::cout << "Animal: 소멸자 호출" << std::endl;
}

void Animal::makeSound() const
{
    std::cout << "Animal: (기본 동물 소리)" << std::endl;
}

std::string Animal::getType() const
{
    return (this->type);
}

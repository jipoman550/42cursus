#include "Cat.hpp"

Cat::Cat()
{
    this->type  = "Cat";
    this->brain = new Brain();
    std::cout << "Cat: 기본 생성자 호출" << std::endl;
}

Cat::Cat(const Cat &other) : AAnimal(other)
{
    this->brain = new Brain(*other.brain);
    std::cout << "Cat: 복사 생성자 호출" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Cat: 대입 연산자 호출" << std::endl;
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
    std::cout << "Cat: 소멸자 호출" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow! Meow!" << std::endl;
}

Brain *Cat::getBrain() const
{
    return (this->brain);
}

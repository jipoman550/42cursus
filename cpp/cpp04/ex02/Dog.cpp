#include "Dog.hpp"

Dog::Dog()
{
    this->type  = "Dog";
    this->brain = new Brain();
    std::cout << "Dog: 기본 생성자 호출" << std::endl;
}

Dog::Dog(const Dog &other) : AAnimal(other)
{
    this->brain = new Brain(*other.brain); // 깊은 복사
    std::cout << "Dog: 복사 생성자 호출" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    std::cout << "Dog: 대입 연산자 호출" << std::endl;
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
    std::cout << "Dog: 소멸자 호출" << std::endl;
}

// ── 순수 가상 함수 구현: 이게 없으면 Dog도 추상 클래스가 됨 ──
void Dog::makeSound() const
{
    std::cout << "Woof! Woof!" << std::endl;
}

Brain *Dog::getBrain() const
{
    return (this->brain);
}

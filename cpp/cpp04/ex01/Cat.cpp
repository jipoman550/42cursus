#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// Cat 클래스 구현 (Brain을 동적 할당)
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: Brain을 힙에 new로 생성 ──
Cat::Cat()
{
    this->type  = "Cat";
    this->brain = new Brain();
    std::cout << "Cat: 기본 생성자 호출 (brain 할당됨)" << std::endl;
}

// ── 복사 생성자: 깊은 복사 ──
Cat::Cat(const Cat &other) : Animal(other)
{
    this->brain = new Brain(*other.brain);
    std::cout << "Cat: 복사 생성자 호출 (brain 깊은 복사)" << std::endl;
}

// ── 대입 연산자: 깊은 복사 ──
Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Cat: 대입 연산자 호출 (brain 깊은 복사)" << std::endl;
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
    std::cout << "Cat: 소멸자 호출 (brain 해제됨)" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow! Meow!" << std::endl;
}

Brain *Cat::getBrain() const
{
    return (this->brain);
}

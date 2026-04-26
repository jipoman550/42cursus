#include "Cat.hpp"

// ────────────────────────────────────────────────────────────
// Cat 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: type을 "Cat"으로 설정 ──
Cat::Cat()
{
    this->type = "Cat";
    std::cout << "Cat: 기본 생성자 호출" << std::endl;
}

// ── 복사 생성자 ──
Cat::Cat(const Cat &other) : Animal(other)
{
    std::cout << "Cat: 복사 생성자 호출" << std::endl;
}

// ── 대입 연산자 ──
Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Cat: 대입 연산자 호출" << std::endl;
    if (this != &other)
        Animal::operator=(other);
    return (*this);
}

// ── 소멸자 ──
Cat::~Cat()
{
    std::cout << "Cat: 소멸자 호출" << std::endl;
}

// ── makeSound(): Cat만의 소리를 출력 ──
void Cat::makeSound() const
{
    std::cout << "Meow! Meow!" << std::endl;
}

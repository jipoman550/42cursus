#include "WrongCat.hpp"

// ────────────────────────────────────────────────────────────
// WrongCat 클래스 구현
// ────────────────────────────────────────────────────────────

WrongCat::WrongCat()
{
    this->type = "WrongCat";
    std::cout << "WrongCat: 기본 생성자 호출" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other)
{
    std::cout << "WrongCat: 복사 생성자 호출" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
    std::cout << "WrongCat: 대입 연산자 호출" << std::endl;
    if (this != &other)
        WrongAnimal::operator=(other);
    return (*this);
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat: 소멸자 호출" << std::endl;
}

// WrongAnimal* 포인터로 WrongCat을 가리키면 이 함수는 절대 호출되지 않음!
// → 이것이 virtual 없이 다형성을 사용했을 때의 문제점
void WrongCat::makeSound() const
{
    std::cout << "WrongCat: Meow! (하지만 부모 포인터로는 불리지 않음)" << std::endl;
}

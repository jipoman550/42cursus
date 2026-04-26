#include "AAnimal.hpp"

// ────────────────────────────────────────────────────────────
// AAnimal 추상 클래스 구현
// 순수 가상 함수(makeSound)의 본체는 여기에 없음 → 자식이 구현해야 함
// ────────────────────────────────────────────────────────────

AAnimal::AAnimal() : type("AAnimal")
{
    std::cout << "AAnimal: 기본 생성자 호출" << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : type(other.type)
{
    std::cout << "AAnimal: 복사 생성자 호출" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other)
{
    std::cout << "AAnimal: 대입 연산자 호출" << std::endl;
    if (this != &other)
        this->type = other.type;
    return (*this);
}

AAnimal::~AAnimal()
{
    std::cout << "AAnimal: 소멸자 호출" << std::endl;
}

std::string AAnimal::getType() const
{
    return (this->type);
}

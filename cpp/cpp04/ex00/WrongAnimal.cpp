#include "WrongAnimal.hpp"

// ────────────────────────────────────────────────────────────
// WrongAnimal 클래스 구현
// ────────────────────────────────────────────────────────────

WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
    std::cout << "WrongAnimal: 기본 생성자 호출" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) : type(other.type)
{
    std::cout << "WrongAnimal: 복사 생성자 호출" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other)
{
    std::cout << "WrongAnimal: 대입 연산자 호출" << std::endl;
    if (this != &other)
        this->type = other.type;
    return (*this);
}

// virtual이 없는 소멸자 → 자식 클래스의 소멸자가 호출되지 않음
WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal: 소멸자 호출" << std::endl;
}

// virtual이 없어서 포인터 타입이 WrongAnimal이면 항상 이 함수가 불림
void WrongAnimal::makeSound() const
{
    std::cout << "WrongAnimal: (잘못된 동물 소리 - virtual 없음)" << std::endl;
}

std::string WrongAnimal::getType() const
{
    return (this->type);
}

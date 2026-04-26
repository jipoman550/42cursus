#include "Cure.hpp"
#include "ICharacter.hpp"

// ────────────────────────────────────────────────────────────
// Cure 클래스 구현
// ────────────────────────────────────────────────────────────

Cure::Cure() : AMateria("cure")
{
    std::cout << "Cure: 기본 생성자 호출" << std::endl;
}

Cure::Cure(const Cure &other) : AMateria(other)
{
    std::cout << "Cure: 복사 생성자 호출" << std::endl;
}

Cure &Cure::operator=(const Cure &other)
{
    std::cout << "Cure: 대입 연산자 호출" << std::endl;
    if (this != &other)
        AMateria::operator=(other);
    return (*this);
}

Cure::~Cure()
{
    std::cout << "Cure: 소멸자 호출" << std::endl;
}

// ── clone(): 새로운 Cure 복사본 반환 ──
AMateria *Cure::clone() const
{
    return (new Cure(*this));
}

// ── use(): 과제 스펙에서 요구하는 출력 형식 ──
void Cure::use(ICharacter &target)
{
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

#include "Ice.hpp"
#include "ICharacter.hpp"

// ────────────────────────────────────────────────────────────
// Ice 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: AMateria("ice")로 type 초기화 ──
Ice::Ice() : AMateria("ice")
{
    std::cout << "Ice: 기본 생성자 호출" << std::endl;
}

// ── 복사 생성자 ──
Ice::Ice(const Ice &other) : AMateria(other)
{
    std::cout << "Ice: 복사 생성자 호출" << std::endl;
}

// ── 대입 연산자 ──
Ice &Ice::operator=(const Ice &other)
{
    std::cout << "Ice: 대입 연산자 호출" << std::endl;
    if (this != &other)
        AMateria::operator=(other);
    return (*this);
}

// ── 소멸자 ──
Ice::~Ice()
{
    std::cout << "Ice: 소멸자 호출" << std::endl;
}

// ── clone(): 새로운 Ice 복사본을 힙에 생성해 반환 ──
AMateria *Ice::clone() const
{
    return (new Ice(*this)); // Ice 복사 생성자 호출
}

// ── use(): 과제 스펙에서 요구하는 출력 형식 ──
void Ice::use(ICharacter &target)
{
    // target.getName()으로 대상 이름을 얻어 출력
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

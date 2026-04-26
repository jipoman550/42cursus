#include "AMateria.hpp"
#include "ICharacter.hpp"

// ────────────────────────────────────────────────────────────
// AMateria 추상 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자 ──
AMateria::AMateria() : type("unknown")
{
    std::cout << "AMateria: 기본 생성자 호출" << std::endl;
}

// ── type을 지정하는 생성자 ──
AMateria::AMateria(std::string const &type) : type(type)
{
    std::cout << "AMateria: 타입 생성자 호출 [" << this->type << "]" << std::endl;
}

// ── 복사 생성자 ──
AMateria::AMateria(const AMateria &other) : type(other.type)
{
    std::cout << "AMateria: 복사 생성자 호출" << std::endl;
}

// ── 대입 연산자 ──
AMateria &AMateria::operator=(const AMateria &other)
{
    std::cout << "AMateria: 대입 연산자 호출" << std::endl;
    if (this != &other)
        this->type = other.type;
    return (*this);
}

// ── 소멸자 ──
AMateria::~AMateria()
{
    std::cout << "AMateria: 소멸자 호출 [" << this->type << "]" << std::endl;
}

// ── type getter: const 참조 반환으로 효율적 읽기 ──
std::string const &AMateria::getType() const
{
    return (this->type);
}

// ── use(): 기본 동작 (자식에서 재정의됨) ──
void AMateria::use(ICharacter &target)
{
    (void)target; // 사용하지 않는 매개변수 경고 억제
    std::cout << "AMateria: (기본 사용)" << std::endl;
}

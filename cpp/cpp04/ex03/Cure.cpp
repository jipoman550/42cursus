#include "Cure.hpp"
#include "ICharacter.hpp"

// ────────────────────────────────────────────────────────────
// Cure 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: AMateria("cure")로 type 초기화 ──
Cure::Cure() : AMateria("cure")
{
	std::cout << "Cure: Default constructor called" << std::endl;
}

// ── 복사 생성자 ──
Cure::Cure(const Cure &other) : AMateria(other)
{
	std::cout << "Cure: Copy constructor called" << std::endl;
}

// ── 대입 연산자 ──
Cure &Cure::operator=(const Cure &other)
{
	std::cout << "Cure: Assignment operator called" << std::endl;
	if (this != &other)
	{
		AMateria::operator=(other);
	}
	return (*this);
}

// ── 소멸자 ──
Cure::~Cure()
{
	std::cout << "Cure: Destructor called" << std::endl;
}

// ── clone(): 새로운 Cure 복사본을 힙에 생성해 반환 ──
AMateria *Cure::clone() const
{
	// 자신과 똑같은 타입의 새 객체를 동적으로 할당하여 반환
	return (new Cure(*this));
}

// ── use(): 과제 스펙에서 요구하는 출력 형식 ──
void Cure::use(ICharacter &target)
{
	// 대상의 이름을 얻어 치유 메시지 출력
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
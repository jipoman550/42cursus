#include "Ice.hpp"
#include "ICharacter.hpp"

// ────────────────────────────────────────────────────────────
// Ice 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: AMateria("ice")로 type 초기화 ──
Ice::Ice() : AMateria("ice")
{
	std::cout << "Ice: Default constructor called" << std::endl;
}

// ── 복사 생성자 ──
Ice::Ice(const Ice &other) : AMateria(other)
{
	std::cout << "Ice: Copy constructor called" << std::endl;
}

// ── 대입 연산자 ──
Ice &Ice::operator=(const Ice &other)
{
	std::cout << "Ice: Assignment operator called" << std::endl;
	if (this != &other)
	{
		AMateria::operator=(other);
	}
	return (*this);
}

// ── 소멸자 ──
Ice::~Ice()
{
	std::cout << "Ice: Destructor called" << std::endl;
}

// ── clone(): 새로운 Ice 복사본을 힙에 생성해 반환 ──
AMateria *Ice::clone() const
{
	// 자신과 똑같은 타입의 새 객체를 동적으로 할당하여 반환 (Prototype 패턴)
	return (new Ice(*this)); //
}

// ── use(): 과제 스펙에서 요구하는 출력 형식 ──
void Ice::use(ICharacter &target)
{
	// target.getName()으로 대상 이름을 얻어 출력
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
#include "Animal.hpp"

// ────────────────────────────────────────────────────────────
// Animal 클래스 구현
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: type을 "Animal"로 설정하고 로그 출력 ──
Animal::Animal() : type("Animal")
{
	std::cout << "Animal: Calling the default constructor" << std::endl;
}

// ── 복사 생성자: 다른 Animal의 type을 복사 ──
Animal::Animal(const Animal &other) : type(other.type)
{
	std::cout << "Animal: Calling the copy constructor" << std::endl;
}

// ── 대입 연산자: 자기 자신 대입 방지 후 type 복사 ──
Animal &Animal::operator=(const Animal &other)
{
	std::cout << "Animal: Calling the assignment operator" << std::endl;
	if (this != &other) // 자기 자신에게 대입하는 경우 방지
	{
		this->type = other.type;
	}
	return (*this); // *this를 반환해 연쇄 대입(a = b = c)을 가능하게 함
}

// ── 가상 소멸자: 다형성 사용 시 반드시 virtual ──
Animal::~Animal()
{
	std::cout << "Animal: Calling the destructor" << std::endl;
}

// ── makeSound(): 기본 동물 소리 (자식 클래스에서 재정의됨) ──
void Animal::makeSound() const
{
	std::cout << "Animal: Animals make sounds." << std::endl;
}

// ── type getter: 외부에서 type 값을 읽을 수 있게 함 ──
std::string Animal::getType() const
{
	return (this->type);
}

#include "Dog.hpp"

// ────────────────────────────────────────────────────────────
// Dog 클래스 구현 (Brain을 동적 할당)
// ────────────────────────────────────────────────────────────

// ── 기본 생성자: Brain을 힙에 new로 생성 ──
Dog::Dog()
{
	this->type  = "Dog";
	this->brain = new Brain(); // 힙에 Brain 객체 동적 생성
	std::cout << "Dog: Call default constructor (brain assigned)" << std::endl;
}

// ── 복사 생성자: 얕은 복사(shallow copy)가 아닌 깊은 복사(deep copy)!
//    단순히 brain = other.brain 으로 복사하면 같은 주소를 두 객체가 공유함
//    → 한 객체가 소멸될 때 다른 객체의 brain도 해제되어 프로그램 충돌!
//    → 따라서 new Brain(*other.brain)으로 새 객체를 만들어야 함
Dog::Dog(const Dog &other) : Animal(other)
{
	this->brain = new Brain(*other.brain); // Brain의 복사 생성자로 깊은 복사
	std::cout << "Dog: Call copy constructor (brain deep copy)" << std::endl;
}

// ── 대입 연산자: 기존 brain 해제 후 새 brain 깊은 복사 ──
Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog: Call assignment operator (brain deep copy)" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);				// 부모 클래스 대입 먼저 처리
		delete this->brain;						// 기존 brain 메모리 해제
		this->brain = new Brain(*other.brain);	// 새 brain 깊은 복사
	}
	return (*this);
}

// ── 소멸자: 동적 할당한 brain을 반드시 delete! ──
Dog::~Dog()
{
	delete this->brain; // 메모리 해제하지 않으면 메모리 누수 발생
	std::cout << "Dog: Destructor called (brain released)" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Woof! Woof! Woof! Woof!" << std::endl;
}

// ── brain 포인터 반환 ──
Brain *Dog::getBrain() const
{
	return (this->brain);
}

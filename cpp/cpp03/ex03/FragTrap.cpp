#include "FragTrap.hpp"

// 기본 생성자
FragTrap::FragTrap() : ClapTrap("Default")
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << _name << " is created by default constructor." << std::endl;
}

// 매개변수 생성자
FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << _name << " is created." << std::endl;
}

// 복사 생성자
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "FragTrap " << _name << " is copied." << std::endl;
}

// 대입 연산자
FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "FragTrap " << _name << " is assigned from " << other._name << "." << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other); // 부모 클래스의 대입 연산자 호출
	}
	return (*this);
}

// 소멸자
FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " is destroyed." << std::endl;
}

// 특수 능력 함수
void FragTrap::highFivesGuys(void)
{
	if (_hitPoints == 0)
	{
		std::cout << "FragTrap " << _name << " is dead and cannot high five!" << std::endl;
		return ;
	}
	std::cout << "FragTrap " << _name << " says: \"Hey guys! Give me a high five! ✋\"" << std::endl;
}

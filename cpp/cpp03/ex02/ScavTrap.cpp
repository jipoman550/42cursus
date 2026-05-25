#include "ScavTrap.hpp"

// 기본 생성자
ScavTrap::ScavTrap() : ClapTrap("Default")
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap " << _name << " is created by default constructor." << std::endl;
}

// 매개변수 생성자
ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap " << _name << " is created." << std::endl;
}

// 복사 생성자
// 부모 클래스의 복사 생성자를 명시적으로 호출하여 속성을 복사
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << "ScavTrap " << _name << " is copied." << std::endl;
}

// 대입 연산자 오버로딩
ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "ScavTrap " << _name << " is assigned from " << other._name << "." << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other); // 부모 클래스의 대입 연산자 호출
	}
	return (*this);
}

// 소멸자
ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << _name << " is destroyed." << std::endl;
}

// 공격 함수 재정의(Override)
// ScavTrap은 차별화된 메시지를 출력해야 함
void ScavTrap::attack(const std::string& target)
{
	if (_hitPoints == 0)
	{
		std::cout << "ScavTrap " << _name << " cannot attack because it has no hit points left!" << std::endl;
		return ;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ScavTrap " << _name << " cannot attack because it has no energy points left!" << std::endl;
		return ;
	}

	_energyPoints--; // 에너지 소모
	std::cout << "ScavTrap " << _name << " fiercely attacks " << target
			  << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

// 특수 능력
void ScavTrap::guardGate()
{
	if (_hitPoints == 0)
	{
		std::cout << "ScavTrap " << _name << " is dead and cannot guard the gate!" << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode." << std::endl;
}

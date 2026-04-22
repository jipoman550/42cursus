#include "DiamondTrap.hpp"

// 기본 생성자
DiamondTrap::DiamondTrap() : ClapTrap("Default_clap_name"), ScavTrap(), FragTrap(), _name("Default")
{
	this->_hitPoints = 100;		// FragTrap
	this->_energyPoints = 50;	// ScavTrap
	this->_attackDamage = 30;	// FragTrap
	std::cout << "DiamondTrap " << this->_name << " is created by default constructor." << std::endl;
}

// 매개변수 생성자
// 가상 상속 상태에서 ClapTrap은 항상 최하위 파생 클래스(DiamondTrap)에서 직접 초기화해야 함
DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
{
	this->_hitPoints = 100;		// FragTrap
	this->_energyPoints = 50;	// ScavTrap
	this->_attackDamage = 30;	// FragTrap
	std::cout << "DiamondTrap " << this->_name << " is created." << std::endl;
}

// 복사 생성자
DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), ScavTrap(other), FragTrap(other), _name(other._name)
{
	std::cout << "DiamondTrap " << this->_name << " is copied." << std::endl;
}

// 대입 연산자
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << "DiamondTrap " << this->_name << " is assigned from " << other._name << "." << std::endl;
	if (this != &other)
	{
		// 부모 클래스들의 대입 연산자를 호출하는 것이 정석입니다
		ClapTrap::operator=(other);
		this->_name = other._name;
	}
	return (*this);
}

// 소멸자
DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << this->_name << " is destroyed." << std::endl;
}

// 특수 능력 whoAmI
void DiamondTrap::whoAmI()
{
	if (this->_hitPoints == 0)
	{
		std::cout << "DiamondTrap " << this->_name << " is dead and cannot speak!" << std::endl;
		return ;
	}
	std::cout << "Hi! I am DiamondTrap [" << this->_name
			  << "], and my ClapTrap name is [" << ClapTrap::_name << "]!" << std::endl;
}

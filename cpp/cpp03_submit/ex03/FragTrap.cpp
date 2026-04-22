#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("Default")
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << _name << " is created by default constructor." << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << _name << " is created." << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "FragTrap " << _name << " is copied." << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "FragTrap " << _name << " is assigned from " << other._name << "." << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other);
	}
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " is destroyed." << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	if (_hitPoints == 0)
	{
		std::cout << "FragTrap " << _name << " is dead and cannot high five!" << std::endl;
		return ;
	}
	std::cout << "FragTrap " << _name << " says: \"Hey guys! Give me a high five! ✋\"" << std::endl;
}

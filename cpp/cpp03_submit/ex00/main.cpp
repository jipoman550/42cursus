#include "ClapTrap.hpp"

int main()
{
	std::cout << "=== 1. Initialization & Orthodox Canonical Form ===" << std::endl;
	ClapTrap a("Penguin");
	ClapTrap b("Duck");
	ClapTrap c;
	c = a;
	ClapTrap d(b);
	std::cout << std::endl;

	std::cout << "=== 2. Energy Depletion Test ===" << std::endl;
	for (int i = 0; i < 11; ++i)
	{
		std::cout << "Action " << i + 1 << " - ";
		a.attack("Duck");
	}
	std::cout << "Try to repair after energy depleted: ";
	a.beRepaired(5);
	std::cout << std::endl;

	std::cout << "=== 3. Death Test ===" << std::endl;
	b.takeDamage(5);
	b.beRepaired(3);
	b.takeDamage(10);

	b.attack("Penguin");
	b.beRepaired(5);
	b.takeDamage(5);
	std::cout << std::endl;

	std::cout << "=== 4. Destruction ===" << std::endl;
	return (0);
}

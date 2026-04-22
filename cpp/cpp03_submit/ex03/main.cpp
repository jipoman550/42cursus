#include "DiamondTrap.hpp"

int main()
{
	std::cout << "=== 1. DiamondTrap Creation ===" << std::endl;
	DiamondTrap diamond("The Second Duck");
	std::cout << std::endl;

	std::cout << "=== 2. DiamondTrap Actions ===" << std::endl;
	diamond.attack("Target");
	diamond.takeDamage(20);
	diamond.beRepaired(10);

	diamond.guardGate();
	diamond.highFivesGuys();
	diamond.whoAmI();
	std::cout << std::endl;

	std::cout << "=== 3. Orthodox Canonical Form Test ===" << std::endl;
	DiamondTrap d2(diamond);
	DiamondTrap d3("Temp");
	d3 = diamond;
	std::cout << std::endl;

	std::cout << "=== 4. Death Test ===" << std::endl;
	diamond.takeDamage(200);
	diamond.attack("Target");
	diamond.whoAmI();
	std::cout << std::endl;

	std::cout << "=== 5. Destruction ===" << std::endl;
	return (0);
}

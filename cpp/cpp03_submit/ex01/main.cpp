#include "ScavTrap.hpp"

int main()
{
	std::cout << "=== 1. ScavTrap Creation ===" << std::endl;
	ScavTrap scav("Guardian");
	std::cout << std::endl;

	std::cout << "=== 2. ScavTrap Actions ===" << std::endl;
	scav.attack("Thief");
	scav.takeDamage(30);
	scav.beRepaired(10);
	scav.guardGate();
	std::cout << std::endl;

	std::cout << "=== 3. Orthodox Canonical Form Test ===" << std::endl;
	ScavTrap scav2(scav);
	ScavTrap scav3("Temp");
	scav3 = scav;
	std::cout << std::endl;

	std::cout << "=== 4. Death Test ===" << std::endl;
	scav.takeDamage(100);
	scav.attack("Thief");
	scav.guardGate();
	std::cout << std::endl;

	std::cout << "=== 5. Destruction ===" << std::endl;
	return (0);
}

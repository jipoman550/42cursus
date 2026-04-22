#include "FragTrap.hpp"

int main()
{
	std::cout << "=== 1. FragTrap Creation ===" << std::endl;
	FragTrap frag("Bomber");
	std::cout << std::endl;

	std::cout << "=== 2. FragTrap Actions ===" << std::endl;
	frag.attack("Dummy");
	frag.takeDamage(50);
	frag.beRepaired(20);
	frag.highFivesGuys();
	std::cout << std::endl;

	std::cout << "=== 3. Orthodox Canonical Form Test ===" << std::endl;
	FragTrap frag2(frag);
	FragTrap frag3("Temp");
	frag3 = frag;
	std::cout << std::endl;

	std::cout << "=== 4. Death Test ===" << std::endl;
	frag.takeDamage(200);
	frag.attack("Dummy");
	frag.highFivesGuys();
	std::cout << std::endl;

	std::cout << "=== 5. Destruction ===" << std::endl;
	return (0);
}

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
	FragTrap frag2(frag); // 복사 생성자
	FragTrap frag3("Temp");
	frag3 = frag;         // 대입 연산자
	std::cout << std::endl;

	std::cout << "=== 4. Death Test ===" << std::endl;
	frag.takeDamage(200);   // 사망
	frag.attack("Dummy");   // 사망 후 공격 불가
	frag.highFivesGuys();   // 사망 후 특수 능력 불가
	std::cout << std::endl;

	std::cout << "=== 5. Destruction ===" << std::endl;
	return (0);
}

#include "ClapTrap.hpp"

int main()
{
	// 1. 객체 생성 및 기본 테스트
	std::cout << "=== 1. Initialization & Orthodox Canonical Form ===" << std::endl;
	ClapTrap a("Penguin");		// 일반 매개변수 생성
	ClapTrap b("Duck");			// 다른 객체
	ClapTrap c;					// 기본 생성자
	c = a;						// 대입 연산자 (Penguin 속성 복사)
	ClapTrap d(b);				// 복사 생성자 (Duck 속성 복사)
	std::cout << std::endl;

	// 2. 에너지 고갈 테스트
	std::cout << "=== 2. Energy Depletion Test ===" << std::endl;
	// 에너지가 기본 10이므로 10번 행동 후 에너지가 고갈되어 동작 불가능해야 함
	for (int i = 0; i < 11; ++i)
	{
		std::cout << "Action " << i + 1 << " - ";
		a.attack("Duck");
	}
	// 11번째 공격은 에너지가 없어 실패.
	std::cout << "Try to repair after energy depleted: ";
	a.beRepaired(5); // 이 경우도 실패해야 함
	std::cout << std::endl;

	// 3. 사망 테스트 (takeDamage는 에너지 소모 안함)
	std::cout << "=== 3. Death Test ===" << std::endl;
	b.takeDamage(5);  // HP 10 -> 5
	b.beRepaired(3);  // HP 5 -> 8 (에너지 1 소모)
	b.takeDamage(10); // HP 8 -> 0 (치명상, 사망)

	// 사망(HP가 0)한 후에는 어떤 행동도 불가능해야 함
	b.attack("Penguin"); // 실패해야 함
	b.beRepaired(5);   // 실패해야 함
	b.takeDamage(5);   // 이미 사망했다고 출력해야 함
	std::cout << std::endl;

	std::cout << "=== 4. Destruction ===" << std::endl;

	return (0); // 이 시점에서 모든 생성된 객체의 소멸자가 호출됨
}

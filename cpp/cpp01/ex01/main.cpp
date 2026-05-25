#include "Zombie.hpp"
#include <sstream> // 숫자를 문자열로 바꾸기 위해 필요합니다.
#include <iostream>

#define ZOMBIE_COUNT 5

int	main(void)
{
	Zombie*	horde;

	// 1. 군단 생성 요청
	horde = zombieHorde(ZOMBIE_COUNT, "HordeMember");
	if (horde == NULL)
		return (1);

	// 2. 테스트 고도화: 소멸 순서를 시각적으로 확인하기 위해 이름에 인덱스 추가
	// 이 과정은 main(테스트 코드)에서 진행하므로 과제 로직을 해치지 않습니다.
	for (int i = 0; i < ZOMBIE_COUNT; i++)
	{
		std::stringstream ss;
		ss << "HordeMember " << i;
		horde[i].setName(ss.str());
	}

	// 3. 모든 좀비가 정상적으로 이름이 설정되었는지 확인 (0번부터 4번까지 출력)
	std::cout << "--- Announcing Zombies ---" << std::endl;
	for (int i = 0; i < ZOMBIE_COUNT; i++)
	{
		horde[i].announce();
	}

	// 4. 소멸자 호출 순서 확인 (중요!)
	// delete[] 호출 시, 이름에 붙은 숫자가 4 -> 3 -> 2 -> 1 -> 0 순으로 출력되는지 확인하세요.
	std::cout << "\n--- Destroying Horde ---" << std::endl;
	delete[] horde;

	return (0);
}

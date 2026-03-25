#include "Zombie.hpp"

#define ZOMBIE_COUNT 5

int	main(void)
{
	Zombie*	horde;

	// 1. 군단 생성 요청
	horde = zombieHorde(ZOMBIE_COUNT, "HordeMember");
	if (horde == NULL)
		return (1);

	// 2. 모든 좀비가 정상적으로 이름이 설정되었는지 확인
	for (int i = 0; i < ZOMBIE_COUNT; i++)
	{
		horde[i].announce();
	}

	// 3. 중요: 'new[]'로 빌린 메모리는 반드시 'delete[]'로 갚아야 함!
	// 그냥 delete를 쓰면 첫 번째 좀비만 죽고 나머지는 메모리 누수가 됨.
	delete[] horde;

	return (0);
}

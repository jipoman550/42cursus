#include "Zombie.hpp"

Zombie*	zombieHorde(int N, std::string name)
{
	// 유효성 검사: 좀비 수가 0 이하면 할당할 필요가 없지.
	if (N <= 0)
		return (NULL);

	// 중요: 'new[]' 연산자를 써서 Zombie N마리 분량의 메모리를 '단 한 번'에 할당함.
	// 이때 N번의 기본 생성자(Zombie())가 호출됨.
	Zombie*	horde = new Zombie[N];

	// 반복문을 돌며 기본 생성자로 만들어진 무명 좀비들에게 이름을 지어줌.
	for (int i = 0; i < N; i++)
	{
		horde[i].setName(name);
	}

	// 군단의 첫 번째 좀비를 가리키는 포인터를 반환함.
	return (horde);
}

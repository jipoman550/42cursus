#include "Zombie.hpp"

int	main(void)
{
	Zombie*	heap_zombie;

	// 1. 힙 할당 테스트:
	// newZombie 안에서 생성된 객체는 함수가 끝나도 살아있음
	heap_zombie = newZombie("HeapZombie");
	heap_zombie->announce();

	// 2. 스택 할당 테스트:
	// randomChump 함수 안에서 만들어진 좀비는 함수가 끝나자마지 죽음 (Destroyed 메시지 출력)
	randomChump("StackZombie");

	// 3. 메모리 해제:
	// 'new'로 만든 객체는 반드시 'delete'를 해줘야 소멸자가 호출됨
	// 만약 delete를 안 하면 memory leak이 발생함
	delete heap_zombie;

	return (0);
}

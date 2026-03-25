#include "Zombie.hpp"

// 이 함수는 'new'를 사용하여 힙 영역에 메모리를 할당함
// 할당된 포인터를 반환하여 함수 외부에서도 이 객체를 제어할 수 있게 함
Zombie*	newZombie(std::string name)
{
	Zombie*	heap_zombie = new Zombie(name);	// 'new' 키워드 사용
	return (heap_zombie);					// 포인터 반환
}

#include "Zombie.hpp"

// 이 함수는 스택 영역에 좀비를 생성함
// 함수가 끝나는 중괄호(})에 도달하면 자동으로 소멸자가 호출됨
void	randomChump(std::string name)
{
	// Zombie	stack_zombie = Zombie(name); // 지역 변수로 생성
	Zombie stack_zombie(name);
	stack_zombie.announce();			 // 함수 종료 시 stack_zombie는 자동으로 파괴됨
}

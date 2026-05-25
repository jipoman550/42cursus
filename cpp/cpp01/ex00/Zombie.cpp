#include "Zombie.hpp"
#include <iostream>

// 생성자 초기화 리스트를 사용해 name을 초기화함 (C++98 권장 방식)
Zombie::Zombie(std::string name) : _name(name)
{
}

// 소멸자: 객체가 메모리에서 사라질 때 자동으로 호출됨
// 디버깅을 위해 좀비 이름을 출력하도록 요구됨
Zombie::~Zombie()
{
	std::cout << this->_name << ": Destroyed..." << std::endl;
}

// 좀비의 행동 구현
void	Zombie::announce(void)
{
	// <name>: BraiiiiiiinnnzzzZ... 형식 준수
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

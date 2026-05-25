#include "Zombie.hpp"
#include <iostream>

// 기본 생성자: 배열 할당 시 자동으로 호출됨. 초기엔 이름이 빈 칸임.
Zombie::Zombie() : _name("")
{
}

// 매개변수 생성자: ex00처럼 한 마리만 힙/스택에 만들 때 유용함.
Zombie::Zombie(std::string name) : _name(name)
{
}

// 소멸자: delete[] 호출 시 N번 호출되어 각 좀비의 이름을 출력함.
Zombie::~Zombie()
{
	std::cout << this->_name << ": Destroyed..." << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

// Setter 함수: 배열 할당 후 각 좀비에게 고유한 이름을 부여함.
void	Zombie::setName(std::string name)
{
	this->_name = name;
}

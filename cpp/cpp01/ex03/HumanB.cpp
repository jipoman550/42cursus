#include "HumanB.hpp"
#include <iostream>

// 생성자: _name을 초기화하고, _weapon 포인터를 NULL로 초기화하여
// 처음에는 무기가 없음을 명시합니다.
HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{
}

// 소멸자
HumanB::~HumanB()
{
}

// setWeapon 함수: 전달받은 Weapon 객체의 주소를 _weapon 포인터에 저장합니다.
void HumanB::setWeapon(Weapon& weapon)
{
	this->_weapon = &weapon;
}

// attack 함수: 무기가 있는지 확인하고 공격 메시지를 출력합니다.
void HumanB::attack()
{
	// 무기 포인터가 NULL이 아닌지 확인하여 방어적인 코드를 작성합니다.
	if (this->_weapon)
	{
		std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
	}
	else
	{
		std::cout << this->_name << " has no weapon to attack" << std::endl;
	}
}

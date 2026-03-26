#include "HumanA.hpp"
#include <iostream>

// 생성자: 멤버 초기화 리스트를 사용하여 _name과 _weapon을 초기화합니다.
// 참조자 멤버(_weapon)는 반드시 초기화 리스트를 통해 초기화되어야 합니다.
HumanA::HumanA(std::string name, Weapon& weapon) : _name(name), _weapon(weapon)
{
}

// 소멸자
HumanA::~HumanA()
{
}

// attack 함수: HumanA가 가진 무기로 공격 메시지를 출력합니다.
void HumanA::attack()
{
	std::cout << this->_name << " attacks with their " << this->_weapon.getType() << std::endl;
}

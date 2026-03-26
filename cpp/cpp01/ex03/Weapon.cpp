#include "Weapon.hpp"
#include <iostream>

// 생성자: 전달받은 type으로 _type 멤버 변수를 초기화합니다.
Weapon::Weapon(std::string type) : _type(type)
{
}

// 소멸자
Weapon::~Weapon()
{
}

// getType 함수: _type 멤버 변수의 const 참조자를 반환합니다.
const std::string& Weapon::getType() const
{
	return this->_type;
}

// setType 함수: 전달받은 type으로 _type 멤버 변수를 설정합니다.
void Weapon::setType(std::string type)
{
	this->_type = type;
}

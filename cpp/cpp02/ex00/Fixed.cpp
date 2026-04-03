#include "Fixed.hpp"
#include <iostream>

// 기본 생성자: private 멤버 변수 val을 0으로 초기화하고, 생성자 호출 메시지를 출력합니다.
Fixed::Fixed() : val(0)
{
	std::cout << "Default constructor called" << std::endl;
}

// 복사 생성자: 다른 Fixed 객체를 복사하여 새로운 객체를 생성합니다.
// 생성자 호출 메시지를 출력하고, src 객체의 값을 현재 객체에 복사합니다.
Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	// *this = src; // 이 방법도 가능하지만, 대입 연산자의 메시지까지 출력될 수 있습니다.
	// 과제 요구사항에 맞춰 복사 생성자 메시지만 출력하기 위해 직접 멤버를 복사합니다.
	this->val = src.val;
}

// 복사 대입 연산자: 한 객체의 값을 다른 객체에 대입합니다.
// 자기 자신에게 대입하는 경우를 방지하기 위해 this와 &rhs 주소를 비교합니다.
Fixed &Fixed::operator=(const Fixed &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		this->val = rhs.val;
	}
	return *this;
}

// 소멸자: 객체가 소멸될 때 호출되며, 소멸자 호출 메시지를 출력합니다.
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// 멤버 함수: 고정 소수점 값의 raw value(정수 값)를 반환합니다.
int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->val;
}

// 멤버 함수: 고정 소수점 값의 raw value를 설정합니다.
void Fixed::setRawBits(int const raw)
{
	this->val = raw;
}
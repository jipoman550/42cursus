#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed() : _val(0)
{
}

Fixed::Fixed(const int n) : _val(n << _bits)
{
}

Fixed::Fixed(const float f) : _val(roundf(f * (1 << _bits)))
{
}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
	{
		this->_val = rhs.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed()
{
}


int Fixed::getRawBits(void) const
{
	return (this->_val);
}

void Fixed::setRawBits(int const raw)
{
	this->_val = raw;
}

float Fixed::toFloat(void) const
{
	return ((float)this->_val / (1 << _bits));
}

int Fixed::toInt(void) const
{
	return (this->_val >> _bits);
}


bool Fixed::operator>(const Fixed &rhs) const
{
	return (this->_val > rhs._val);
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return (this->_val < rhs._val);
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return (this->_val >= rhs._val);
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return (this->_val <= rhs._val);
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return (this->_val == rhs._val);
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return (this->_val != rhs._val);
}

Fixed Fixed::operator+(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

// ================================================================
// 증감 연산자 (4개)
// 고정 소수점에서 표현 가능한 가장 작은 단위는 1/2^8 = 1/256 ≈ 0.00390625
// 이는 내부 val을 1만큼 증가/감소시키는 것과 동일
// ================================================================

// 전위 증가 (++a): 먼저 val을 1 증가시킨 뒤, 변경된 자기 자신의 참조를 반환
// 호출자는 증가된 값을 바로 사용할 수 있음
Fixed &Fixed::operator++(void)
{
	this->_val++;
	return (*this);
}

// 후위 증가 (a++): 증가하기 전의 값을 임시 복사본에 저장한 뒤 val을 증가
// 복사본(증가 전 값)을 반환하므로 반환 타입이 Fixed(값)이어야 함
// ※ 더미 int 매개변수로 전위와 구분 (C++ 문법 규약)
Fixed Fixed::operator++(int)
{
	Fixed tmp(*this); // 증가 전 상태를 보존
	this->_val++;      // 실제 값을 증가
	return (tmp);       // 증가 전 복사본을 반환
}

// 전위 감소 (--a): val을 1 감소시키고 자기 자신의 참조를 반환
Fixed &Fixed::operator--(void)
{
	this->_val--;
	return (*this);
}

// 후위 감소 (a--): 감소 전 복사본을 반환하고, 실제 값은 감소
Fixed Fixed::operator--(int)
{
	Fixed tmp(*this); // 감소 전 상태를 보존
	this->_val--;      // 실제 값을 감소
	return (tmp);       // 감소 전 복사본을 반환
}

// ================================================================
// Static 멤버 함수: min, max (각 2개씩 총 4개)
// 객체 생성 없이 Fixed::min(a, b) 형태로 호출 가능
// 두 Fixed 중 더 작은/큰 값의 참조를 반환
// const 버전: const 객체를 인자로 받을 때 사용 (const 정확성 보장)
// ================================================================

// min (일반 참조 버전): 두 Fixed 중 작은 값의 참조를 반환
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a <= b)
		return (a);
	return (b);
}

// min (const 참조 버전): const 객체에 대해 동작하는 버전
const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a <= b)
		return (a);
	return (b);
}

// max (일반 참조 버전): 두 Fixed 중 큰 값의 참조를 반환
Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a >= b)
		return (a);
	return (b);
}

// max (const 참조 버전): const 객체에 대해 동작하는 버전
const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a >= b)
		return (a);
	return (b);
}

// ================================================================
// operator<< 오버로딩: Fixed 객체를 ostream에 출력
// friend 키워드 없이, public 멤버 함수 toFloat()를 호출하여
// 고정 소수점 값을 부동 소수점 형태로 출력
// ================================================================
std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}

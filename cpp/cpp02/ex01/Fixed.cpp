#include "Fixed.hpp"
#include <cmath> // roundf 함수를 사용하기 위해 포함

// 기본 생성자: val을 0으로 초기화
Fixed::Fixed() : _val(0)
{
	std::cout << "Default constructor called" << std::endl;
}

// 정수 생성자: 정수를 고정 소수점으로 변환
// 정수 n을 왼쪽으로 bits(8)만큼 비트 시프트하여 저장
// 예: n=5 → val = 5 << 8 = 5 * 256 = 1280
// 이는 10진수에서 소수점 자리를 확보하기 위해 5를 50으로 저장하는 것과 같은 원리
Fixed::Fixed(const int n) : _val(n << _bits)
{
	std::cout << "Int constructor called" << std::endl;
}

// 부동 소수점 생성자: float를 고정 소수점으로 변환
// float는 비트 시프트(<<)를 직접 할 수 없으므로, (1 << bits) = 256을 곱한 뒤
// roundf로 반올림하여 가장 가까운 정수로 저장
// 예: f=1.5 → val = roundf(1.5 * 256) = roundf(384.0) = 384
Fixed::Fixed(const float f) : _val(roundf(f * (1 << _bits)))
{
	std::cout << "Float constructor called" << std::endl;
}

// 복사 생성자: 다른 Fixed 객체의 값을 복사하여 새 객체 생성
Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	// 대입 연산자를 호출하여 코드 재사용 및 서브젝트 요구사항 충족
	*this = src;
}

// 복사 대입 연산자: 한 객체의 값을 다른 객체에 대입
// 자기 자신에게 대입하는 경우를 방지하기 위해 주소 비교
Fixed &Fixed::operator=(const Fixed &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

// 소멸자: 객체 소멸 시 호출
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// getRawBits: 고정 소수점의 raw value(내부 정수 값)를 반환
// ex01에서는 getRawBits 호출 메시지를 출력하지 않음 (서브젝트 출력 예시에 맞춤)
int Fixed::getRawBits(void) const
{
	return (this->_val);
}

// setRawBits: 고정 소수점의 raw value를 직접 설정
void Fixed::setRawBits(int const raw)
{
	this->_val = raw;
}

// toFloat: 고정 소수점 값을 부동 소수점(float)으로 변환
// 저장된 정수 값을 (1 << bits) = 256으로 나누어 원래의 실수 값을 복원
// 예: val=384 → 384 / 256.0 = 1.5
float Fixed::toFloat(void) const
{
	return ((float)this->_val / (1 << _bits));
}

// toInt: 고정 소수점 값을 정수(int)로 변환
// 저장된 값을 오른쪽으로 bits(8)만큼 비트 시프트하여 소수부를 버림
// 예: val=384 (실수 1.5) → 384 >> 8 = 1 (소수부 절삭)
int Fixed::toInt(void) const
{
	return (this->_val >> _bits);
}

// operator<< 오버로딩: Fixed 객체를 ostream에 출력
// friend 키워드를 사용하지 않고, public 멤버 함수인 toFloat()를 호출하여
// 고정 소수점 값을 부동 소수점 형태로 출력
std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}

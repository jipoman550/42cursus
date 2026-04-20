#include "Fixed.hpp"
#include <cmath> // roundf 함수를 사용하기 위해 포함

// ================================================================
// Orthodox Canonical Class Form (정통 표준 클래스 형태)
// ================================================================

// 기본 생성자: val을 0으로 초기화
Fixed::Fixed() : _val(0)
{
}

// 정수 생성자: 정수를 고정 소수점으로 변환
// 정수 n을 왼쪽으로 bits(8)만큼 비트 시프트하여 저장
// 예: n=5 → val = 5 << 8 = 5 * 256 = 1280
Fixed::Fixed(const int n) : _val(n << _bits)
{
}

// 부동 소수점 생성자: float를 고정 소수점으로 변환
// float는 비트 시프트를 직접 할 수 없으므로 (1 << bits) = 256을 곱한 뒤
// roundf로 반올림하여 가장 가까운 정수로 저장
// 예: f=42.42 → val = roundf(42.42 * 256) = roundf(10859.52) = 10860
Fixed::Fixed(const float f) : _val(roundf(f * (1 << _bits)))
{
}

// 복사 생성자: 다른 Fixed 객체의 raw bits를 그대로 복사
Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

// 복사 대입 연산자: 자기 대입(self-assignment)을 방지하고 값을 복사
Fixed &Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

// 소멸자
Fixed::~Fixed()
{
}

// ================================================================
// 기존 멤버 함수
// ================================================================

// getRawBits: 고정 소수점의 raw value(내부 정수 값)를 반환
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
// 오른쪽으로 bits(8)만큼 비트 시프트하여 소수부를 절삭
// 예: val=384 (실수 1.5) → 384 >> 8 = 1
int Fixed::toInt(void) const
{
	return (this->_val >> _bits);
}

// ================================================================
// 비교 연산자 (6개)
// 고정 소수점의 내부 정수(val)는 동일한 스케일(2^8)로 저장되어 있으므로
// val끼리 직접 비교하면 실제 수치 비교와 동일한 결과를 얻을 수 있음
// ================================================================

// 크다 (>): 왼쪽 피연산자가 오른쪽보다 큰지 판별
bool Fixed::operator>(const Fixed &rhs) const
{
	return (this->_val > rhs._val);
}

// 작다 (<): 왼쪽 피연산자가 오른쪽보다 작은지 판별
bool Fixed::operator<(const Fixed &rhs) const
{
	return (this->_val < rhs._val);
}

// 크거나 같다 (>=)
bool Fixed::operator>=(const Fixed &rhs) const
{
	return (this->_val >= rhs._val);
}

// 작거나 같다 (<=)
bool Fixed::operator<=(const Fixed &rhs) const
{
	return (this->_val <= rhs._val);
}

// 같다 (==): 두 고정 소수점이 동일한 값인지 판별
bool Fixed::operator==(const Fixed &rhs) const
{
	return (this->_val == rhs._val);
}

// 같지 않다 (!=)
bool Fixed::operator!=(const Fixed &rhs) const
{
	return (this->_val != rhs._val);
}

// ================================================================
// 산술 연산자 (4개)
// 연산 결과로 새로운 Fixed 객체를 생성하여 반환 (원본은 변경하지 않음)
// ================================================================

// 덧셈 (+): 동일한 스케일의 고정 소수점이므로 val끼리 그냥 더하면 됨
// 예: 1.5 + 2.0 → (384 + 512) = 896 → 896 / 256 = 3.5
Fixed Fixed::operator+(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

// 뺄셈 (-): 덧셈과 마찬가지로 val끼리 빼면 됨
// 예: 2.0 - 1.5 → (512 - 384) = 128 → 128 / 256 = 0.5
Fixed Fixed::operator-(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

// 곱셈 (*): (a * 2^8) * (b * 2^8) = a*b * 2^16 이 되어 스케일이 두 배가 됨
// 따라서 곱한 후 다시 2^8로 나눠줘야 하는데, 가장 안전한 방법은
// toFloat()로 실수 변환 후 곱하고 다시 Fixed로 생성하는 것
// 이렇게 하면 오버플로우 걱정 없이 정확한 결과를 얻을 수 있음
Fixed Fixed::operator*(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

// 나눗셈 (/): val끼리 그냥 나누면 스케일(2^8)이 상쇄되어 사라짐
// 따라서 분자를 먼저 2^8 스케일로 올린 후 나눠야 하는데,
// toFloat() 방식이 가장 간단하고 안전함
// ※ 0으로 나누는 경우: 서브젝트에서 "프로그램이 중단되어도 무방"하다고 명시
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
	return (tmp);     // 증가 전 복사본을 반환
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
	return (tmp);     // 감소 전 복사본을 반환
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

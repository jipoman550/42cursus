#include "Point.hpp"

// 기본 생성자: 초기화 리스트를 사용하여 const 멤버인 x와 y를 0으로 초기화
Point::Point() : x(0), y(0)
{
}

// float 생성자: 입력받은 float 값을 Fixed 객체로 변환하여 초기화 리스트로 설정
Point::Point(const float x, const float y) : x(x), y(y)
{
}

// 복사 생성자: 다른 Point 객체의 x, y 값을 복사하여 생성
Point::Point(const Point &src) : x(src.x), y(src.y)
{
}

// 복사 대입 연산자:
// const 멤버 변수는 생성 시점 이외에는 값을 변경할 수 없음
// 따라서 대입 연산자가 호출되어도 x나 y 값을 덮어씌울 수 없으므로 아무 동작도 하지 않고
// 자기 자신(*this)의 참조만 반환함
Point &Point::operator=(const Point &rhs)
{
	// 할당할 수 없으므로 컴파일러 경고를 피하기 위해 rhs를 무시
	(void)rhs;
	return *this;
}

// 소멸자
Point::~Point()
{
}

// Getter: x의 고정 소수점 값 반환
Fixed Point::getX(void) const
{
	return this->x;
}

// Getter: y의 고정 소수점 값 반환
Fixed Point::getY(void) const
{
	return this->y;
}

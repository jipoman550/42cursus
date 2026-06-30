#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
public:
	// 생성자 및 소멸자
	vect2(int x = 0, int y = 0);
	vect2(const vect2& other);
	~vect2();

	// 대입 연산자
	vect2& operator=(const vect2& other);

	// 원소 접근
	int& operator[](int index);
	const int& operator[](int index) const;

	// 복합 대입 연산자
	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int scalar);

	// 증감 연산자
	vect2& operator++();      // 전위
	vect2 operator++(int);   // 후위
	vect2& operator--();      // 전위
	vect2 operator--(int);   // 후위

	// 단항 부정 연산자
	vect2 operator-() const;

private:
	int data[2];
};

// 비멤버 함수 연산자
std::ostream& operator<<(std::ostream& os, const vect2& v);
vect2 operator+(vect2 lhs, const vect2& rhs);
vect2 operator-(vect2 lhs, const vect2& rhs);
vect2 operator*(vect2 v, int scalar);
vect2 operator*(int scalar, vect2 v);
bool operator==(const vect2& lhs, const vect2& rhs);
bool operator!=(const vect2& lhs, const vect2& rhs);

#endif // VECT2_HPP
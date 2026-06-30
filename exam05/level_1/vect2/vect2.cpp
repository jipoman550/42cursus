#include "vect2.hpp"

// 생성자
vect2::vect2(int x, int y) {
	data[0] = x;
	data[1] = y;
}

vect2::vect2(const vect2& other) {
	data[0] = other.data[0];
	data[1] = other.data[1];
}

// 소멸자
vect2::~vect2() {}

// 대입 연산자
vect2& vect2::operator=(const vect2& other) {
	if (this != &other) {
		data[0] = other.data[0];
		data[1] = other.data[1];
	}
	return *this;
}

// 원소 접근
int& vect2::operator[](int index) {
	return data[index];
}

const int& vect2::operator[](int index) const {
	return data[index];
}

// 복합 대입 연산자
vect2& vect2::operator+=(const vect2& other) {
	data[0] += other.data[0];
	data[1] += other.data[1];
	return *this;
}

vect2& vect2::operator-=(const vect2& other) {
	data[0] -= other.data[0];
	data[1] -= other.data[1];
	return *this;
}

vect2& vect2::operator*=(int scalar) {
	data[0] *= scalar;
	data[1] *= scalar;
	return *this;
}

// 증감 연산자
vect2& vect2::operator++() { // 전위
	++data[0];
	++data[1];
	return *this;
}

vect2 vect2::operator++(int) { // 후위
	vect2 temp = *this;
	++(*this);
	return temp;
}

vect2& vect2::operator--() { // 전위
	--data[0];
	--data[1];
	return *this;
}

vect2 vect2::operator--(int) { // 후위
	vect2 temp = *this;
	--(*this);
	return temp;
}

// 단항 부정 연산자
vect2 vect2::operator-() const {
	return vect2(-data[0], -data[1]);
}

// 비멤버 함수 연산자 구현
std::ostream& operator<<(std::ostream& os, const vect2& v) {
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}

vect2 operator+(vect2 lhs, const vect2& rhs) { return lhs += rhs; }
vect2 operator-(vect2 lhs, const vect2& rhs) { return lhs -= rhs; }
vect2 operator*(vect2 v, int scalar) { return v *= scalar; }
vect2 operator*(int scalar, vect2 v) { return v *= scalar; }
bool operator==(const vect2& lhs, const vect2& rhs) { return lhs[0] == rhs[0] && lhs[1] == rhs[1]; }
bool operator!=(const vect2& lhs, const vect2& rhs) { return !(lhs == rhs); }
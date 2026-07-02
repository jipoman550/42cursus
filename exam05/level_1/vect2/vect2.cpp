#include "vect2.hpp"

// --- 생성자 ---
// 기본 생성자 및 초기화 생성자 구현
vect2::vect2(int x, int y) {
	// 멤버 변수 data 배열에 x, y 값을 초기화합니다.
	data[0] = x;
	data[1] = y;
}

// 복사 생성자 구현
vect2::vect2(const vect2& other) {
	// 다른 vect2 객체의 data 값을 현재 객체의 data로 복사합니다.
	data[0] = other.data[0];
	data[1] = other.data[1];
}

// --- 소멸자 ---
// 소멸자 구현. 동적으로 할당된 메모리가 없으므로 비워둡니다.
vect2::~vect2() {}

// --- 대입 연산자 ---
// 대입 연산자 구현
vect2& vect2::operator=(const vect2& other) {
	// 자기 자신에게 대입하는 경우를 방지합니다 (예: v1 = v1).
	if (this != &other) {
		// 다른 객체의 데이터를 현재 객체로 복사합니다.
		data[0] = other.data[0];
		data[1] = other.data[1];
	}
	return *this; // 연쇄적인 대입(v1 = v2 = v3)을 위해 현재 객체의 참조를 반환합니다.
}

// --- 원소 접근 ---
// 인덱스 연산자 구현 (읽기/쓰기)
int& vect2::operator[](int index) {
	return data[index]; // 해당 인덱스의 원소에 대한 참조를 반환합니다.
}

// const 버전 인덱스 연산자 구현 (읽기 전용)
const int& vect2::operator[](int index) const {
	return data[index]; // 해당 인덱스의 원소에 대한 const 참조를 반환합니다.
}

// --- 복합 대입 연산자 ---
// 덧셈 복합 대입 연산자 구현
vect2& vect2::operator+=(const vect2& other) {
	// 각 원소별로 덧셈을 수행합니다.
	data[0] += other.data[0];
	data[1] += other.data[1];
	return *this; // 연산을 마친 현재 객체의 참조를 반환합니다.
}

// 뺄셈 복합 대입 연산자 구현
vect2& vect2::operator-=(const vect2& other) {
	// 각 원소별로 뺄셈을 수행합니다.
	data[0] -= other.data[0];
	data[1] -= other.data[1];
	return *this; // 연산을 마친 현재 객체의 참조를 반환합니다.
}

// 스칼라 곱셈 복합 대입 연산자 구현
vect2& vect2::operator*=(int scalar) {
	// 각 원소에 스칼라 값을 곱합니다.
	data[0] *= scalar;
	data[1] *= scalar;
	return *this; // 연산을 마친 현재 객체의 참조를 반환합니다.
}

// --- 증감 연산자 ---
// 전위 증가 연산자 구현
vect2& vect2::operator++() {
	// 각 원소를 1씩 증가시킵니다.
	++data[0];
	++data[1];
	return *this; // 증가된 현재 객체의 참조를 반환합니다.
}

// 후위 증가 연산자 구현
vect2 vect2::operator++(int) {
	vect2 temp = *this; // 변경 전의 상태를 임시 객체에 저장합니다.
	++(*this);          // 현재 객체의 값을 증가시킵니다 (전위 증가 연산자 호출).
	return temp;        // 변경 전의 값을 반환합니다.
}

// 전위 감소 연산자 구현
vect2& vect2::operator--() {
	// 각 원소를 1씩 감소시킵니다.
	--data[0];
	--data[1];
	return *this; // 감소된 현재 객체의 참조를 반환합니다.
}

// 후위 감소 연산자 구현
vect2 vect2::operator--(int) {
	vect2 temp = *this; // 변경 전의 상태를 임시 객체에 저장합니다.
	--(*this);          // 현재 객체의 값을 감소시킵니다 (전위 감소 연산자 호출).
	return temp;        // 변경 전의 값을 반환합니다.
}

// --- 단항 부정 연산자 ---
// 단항 부정 연산자 구현
vect2 vect2::operator-() const {
	return vect2(-data[0], -data[1]); // 각 원소의 부호를 바꾼 새로운 vect2 객체를 생성하여 반환합니다.
}

// --- 비멤버 함수 연산자 구현 ---
// 출력 스트림 연산자 구현
std::ostream& operator<<(std::ostream& os, const vect2& v) {
	os << "{" << v[0] << ", " << v[1] << "}"; // "{x, y}" 형식으로 출력 스트림에 씁니다.
	return os; // 연쇄적인 출력을 위해 출력 스트림의 참조를 반환합니다.
}

// 덧셈 연산자 구현. 복합 대입 연산자를 재사용합니다.
// lhs를 값으로 받아 복사본을 만들고, 여기에 rhs를 더한 후 반환합니다.
vect2 operator+(vect2 lhs, const vect2& rhs) { return lhs += rhs; }

// 뺄셈 연산자 구현. 복합 대입 연산자를 재사용합니다.
vect2 operator-(vect2 lhs, const vect2& rhs) { return lhs -= rhs; }

// 스칼라 곱셈 연산자 구현 (v * scalar). 복합 대입 연산자를 재사용합니다.
vect2 operator*(vect2 v, int scalar) { return v *= scalar; }

// 스칼라 곱셈 연산자 구현 (scalar * v). 위 연산자를 재사용합니다.
vect2 operator*(int scalar, vect2 v) { return v *= scalar; }

// 동등 비교 연산자 구현. 각 원소가 모두 같은지 비교합니다.
bool operator==(const vect2& lhs, const vect2& rhs) { return lhs[0] == rhs[0] && lhs[1] == rhs[1]; }

// 비동등 비교 연산자 구현. 동등 비교 연산자(==)의 결과를 부정하여 재사용합니다.
bool operator!=(const vect2& lhs, const vect2& rhs) { return !(lhs == rhs); }
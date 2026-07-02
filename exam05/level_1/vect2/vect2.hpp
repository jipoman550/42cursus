#ifndef VECT2_HPP // 헤더 가드: 헤더 파일이 두 번 이상 포함되는 것을 방지합니다.
#define VECT2_HPP // VECT2_HPP가 정의되지 않았을 경우, 아래 코드를 컴파일하고 VECT2_HPP를 정의합니다.

#include <iostream> // std::ostream을 사용하기 위해 포함합니다.

class vect2 {
public:
	// --- 생성자 및 소멸자 ---
	vect2(int x = 0, int y = 0); // 기본 생성자 및 초기화 생성자. x, y 좌표를 받아서 벡터를 생성합니다. 기본값은 0입니다.
	vect2(const vect2& other);   // 복사 생성자. 다른 vect2 객체를 복사하여 새로운 객체를 생성합니다.
	~vect2();                    // 소멸자. 객체가 소멸될 때 호출됩니다.

	// --- 대입 연산자 ---
	vect2& operator=(const vect2& other); // 대입 연산자. 다른 vect2 객체의 값을 현재 객체에 대입합니다.

	// --- 원소 접근 ---
	int& operator[](int index);             // 인덱스 연산자. 벡터의 원소에 접근합니다 (읽기/쓰기 가능).
	const int& operator[](int index) const; // const 버전 인덱스 연산자. const 객체의 원소에 접근합니다 (읽기 전용).

	// --- 복합 대입 연산자 ---
	vect2& operator+=(const vect2& other); // 덧셈 복합 대입 연산자 (v1 += v2).
	vect2& operator-=(const vect2& other); // 뺄셈 복합 대입 연산자 (v1 -= v2).
	vect2& operator*=(int scalar);         // 스칼라 곱셈 복합 대입 연산자 (v1 *= 2).

	// --- 증감 연산자 ---
	vect2& operator++();      // 전위 증가 연산자 (++v).
	vect2 operator++(int);   // 후위 증가 연산자 (v++).
	vect2& operator--();      // 전위 감소 연산자 (--v).
	vect2 operator--(int);   // 후위 감소 연산자 (v--).

	// --- 단항 부정 연산자 ---
	vect2 operator-() const; // 단항 부정 연산자 (-v). 벡터의 각 원소의 부호를 바꿉니다.

private:
	int data[2]; // 벡터의 x, y 좌표를 저장하는 정수 배열.
};

// --- 비멤버 함수 연산자 ---
std::ostream& operator<<(std::ostream& os, const vect2& v); // 출력 스트림 연산자 (std::cout << v).
vect2 operator+(vect2 lhs, const vect2& rhs);               // 덧셈 연산자 (v1 + v2).
vect2 operator-(vect2 lhs, const vect2& rhs);               // 뺄셈 연산자 (v1 - v2).
vect2 operator*(vect2 v, int scalar);                       // 스칼라 곱셈 연산자 (v * 2).
vect2 operator*(int scalar, vect2 v);                       // 스칼라 곱셈 연산자 (2 * v).
bool operator==(const vect2& lhs, const vect2& rhs);        // 동등 비교 연산자 (v1 == v2).
bool operator!=(const vect2& lhs, const vect2& rhs);        // 비동등 비교 연산자 (v1 != v2).

#endif // VECT2_HPP
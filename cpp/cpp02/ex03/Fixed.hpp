#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	private:
		int					val; // 고정 소수점 값을 저장할 정수 (raw bits)
		static const int	bits = 8; // 소수부 비트 수 (항상 8로 고정)

	public:
		// ============================================================
		// Orthodox Canonical Class Form (정통 표준 클래스 형태)
		// ============================================================
		Fixed(); // 기본 생성자
		Fixed(const Fixed &src); // 복사 생성자
		Fixed &operator=(const Fixed &rhs); // 복사 대입 연산자
		~Fixed(); // 소멸자

		// ============================================================
		// 추가 생성자 (ex01에서 추가)
		// ============================================================
		Fixed(const int n); // 정수를 고정 소수점으로 변환하는 생성자
		Fixed(const float f); // 부동 소수점을 고정 소수점으로 변환하는 생성자

		// ============================================================
		// 멤버 함수
		// ============================================================
		int getRawBits(void) const; // raw value 반환
		void setRawBits(int const raw); // raw value 설정
		float toFloat(void) const; // 고정 소수점 -> 부동 소수점 변환
		int toInt(void) const; // 고정 소수점 -> 정수 변환

		// ============================================================
		// 비교 연산자 (6개) - ex02에서 새로 추가
		// 두 Fixed 객체의 대소 관계를 판별
		// 내부적으로 스케일링된 정수(val)끼리 비교하면 됨
		// ============================================================
		bool operator>(const Fixed &rhs) const; // 크다
		bool operator<(const Fixed &rhs) const; // 작다
		bool operator>=(const Fixed &rhs) const; // 크거나 같다
		bool operator<=(const Fixed &rhs) const; // 작거나 같다
		bool operator==(const Fixed &rhs) const; // 같다
		bool operator!=(const Fixed &rhs) const; // 같지 않다

		// ============================================================
		// 산술 연산자 (4개) - ex02에서 새로 추가
		// 고정 소수점 사칙연산. 새로운 Fixed 객체를 반환
		// ============================================================
		Fixed operator+(const Fixed &rhs) const; // 덧셈
		Fixed operator-(const Fixed &rhs) const; // 뺄셈
		Fixed operator*(const Fixed &rhs) const; // 곱셈
		Fixed operator/(const Fixed &rhs) const; // 나눗셈

		// ============================================================
		// 증감 연산자 (4개) - ex02에서 새로 추가
		// 가장 작은 표현 가능한 ε(1/256)만큼 증가/감소
		// 전위(prefix): 값을 변경 후 자기 자신의 참조를 반환
		// 후위(postfix): 변경 전 복사본을 반환 후 값을 변경
		// ============================================================
		Fixed &operator++(void); // 전위 증가 (++a)
		Fixed operator++(int); // 후위 증가 (a++) — 더미 int로 구분
		Fixed &operator--(void); // 전위 감소 (--a)
		Fixed operator--(int); // 후위 감소 (a--) — 더미 int로 구분

		// ============================================================
		// Static 멤버 함수: min, max (각각 2개씩, 총 4개) - ex02에서 새로 추가
		// 객체를 생성하지 않고도 호출 가능 (Fixed::min(a, b))
		// const 버전: const 객체에 대해서도 안전하게 호출 가능
		// ============================================================
		static Fixed &min(Fixed &a, Fixed &b); // 일반 참조 버전
		static const Fixed &min(const Fixed &a, const Fixed &b); // const 참조 버전
		static Fixed &max(Fixed &a, Fixed &b); // 일반 참조 버전
		static const Fixed &max(const Fixed &a, const Fixed &b); // const 참조 버전
};

// operator<< 오버로딩: friend 키워드 없이 외부에서 선언
// toFloat()를 호출하여 고정 소수점 값을 실수로 출력
std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif

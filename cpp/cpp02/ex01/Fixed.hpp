#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	private:
		int					_val; // 고정 소수점 값을 저장할 정수 (raw bits)
		static const int	_bits = 8; // 소수부 비트 수 (항상 8로 고정)

	public:
		// Orthodox Canonical Class Form
		Fixed(); // 기본 생성자
		Fixed(const Fixed &src); // 복사 생성자
		Fixed &operator=(const Fixed &rhs); // 복사 대입 연산자
		~Fixed(); // 소멸자

		// 추가 생성자 (ex01에서 새로 추가)
		Fixed(const int n); // 정수를 고정 소수점으로 변환하는 생성자
		Fixed(const float f); // 부동 소수점을 고정 소수점으로 변환하는 생성자

		// 멤버 함수
		int getRawBits(void) const; // raw value 반환
		void setRawBits(int const raw); // raw value 설정

		// 변환 함수 (ex01에서 새로 추가)
		float toFloat(void) const; // 고정 소수점 -> 부동 소수점 변환
		int toInt(void) const; // 고정 소수점 -> 정수 변환
};

// operator<< 오버로딩: friend 키워드 없이 외부에서 선언
// toFloat()를 호출하여 고정 소수점 값을 실수로 출력
std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif

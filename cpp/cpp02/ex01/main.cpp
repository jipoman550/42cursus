#include <iostream>
#include "Fixed.hpp"

// 서브젝트에서 제공된 테스트 코드
int main(void)
{
	// 기본 생성자로 a 생성 (val = 0)
	Fixed a;

	// 정수 생성자로 b 생성: 1234를 고정 소수점으로 변환
	// 내부적으로 val = 1234 << 8 = 315904
	Fixed const b(10);

	// 부동 소수점 생성자로 c 생성: 42.42를 고정 소수점으로 변환
	// 내부적으로 val = roundf(42.42 * 256) = roundf(10859.52) = 10860
	Fixed const c(42.42f);

	// 복사 생성자로 d 생성: b의 값을 복사
	Fixed const d(b);

	// 대입 연산자로 a에 Fixed(1234.4321f)의 값을 대입
	// Fixed(1234.4321f)는 임시 객체로 생성된 후, a에 대입되고 소멸
	a = Fixed(1234.4321f);

	// operator<< 를 이용한 출력: toFloat()가 호출되어 실수 형태로 출력
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	// toInt()를 이용한 출력: 고정 소수점 값을 정수로 변환 (소수부 절삭)
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	return 0;
}

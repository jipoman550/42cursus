#include "Fixed.hpp"

int main(void)
{
	// 기본 생성자를 사용하여 'a' 객체 생성
	Fixed a;

	// 복사 생성자를 사용하여 'a'를 복사한 'b' 객체 생성
	Fixed b(a);

	// 기본 생성자를 사용하여 'c' 객체 생성
	Fixed c;

	// 복사 대입 연산자를 사용하여 'c'에 'b'를 대입
	c = b;

	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;

	return 0;
}
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string.h>

class Fixed
{
	private:
		int					_val; // 고정 소수점 값을 저장할 정수
		static const int	_bits = 8; // 소수부 비트 수 (항상 8)

	public:
		// Orthodox Canonical Class Form
		Fixed();
		Fixed(const Fixed &src);
		Fixed &operator=(const Fixed &rhs);
		~Fixed();

		// 멤버 함수
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif
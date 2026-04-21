#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string.h>

class Fixed
{
	private:
		int					_val;
		static const int	_bits = 8;

	public:
		Fixed();
		Fixed(const Fixed &src);
		Fixed &operator=(const Fixed &rhs);
		~Fixed();

		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	private:
		int val;
		static const int bits = 8;
	public:
		Fixed(): val(0){};
		~Fixed();
		Fixed &operator=(Fixed const &rhs);
		Fixed(Fixed const &src);

}
#endif
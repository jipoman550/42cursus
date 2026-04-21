#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
	private:
		Fixed const x;
		Fixed const y;

	public:
		Point();
		Point(const Point &src);
		Point &operator=(const Point &rhs);
		~Point();

		Point(const float x, const float y);

		Fixed getX(void) const;
		Fixed getY(void) const;
};

#endif

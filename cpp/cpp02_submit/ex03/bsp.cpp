#include "Point.hpp"

static Fixed getCrossProduct(Point const p1, Point const p2, Point const p3)
{
	Fixed v1_x = p2.getX() - p1.getX();
	Fixed v1_y = p2.getY() - p1.getY();

	Fixed v2_x = p3.getX() - p1.getX();
	Fixed v2_y = p3.getY() - p1.getY();

	return ((v1_x * v2_y) - (v1_y * v2_x));
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed cp1 = getCrossProduct(a, b, point);
	Fixed cp2 = getCrossProduct(b, c, point);
	Fixed cp3 = getCrossProduct(c, a, point);

	if ((cp1 > Fixed(0) && cp2 > Fixed(0) && cp3 > Fixed(0)) ||
		(cp1 < Fixed(0) && cp2 < Fixed(0) && cp3 < Fixed(0)))
	{
		return (true);
	}

	return (false);
}

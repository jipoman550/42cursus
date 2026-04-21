#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	Point const a(0.0f, 0.0f);
	Point const b(10.0f, 0.0f);
	Point const c(0.0f, 10.0f);

	std::cout << "========== BSP Test ==========" << std::endl;

	// Test 1: Point strictly inside the triangle
	Point const p1(2.0f, 2.0f);
	std::cout << "Test 1: p1(2, 2) is inside? ";
	if (bsp(a, b, c, p1))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;

	// Test 2: Point outside the triangle (top-right)
	Point const p2(10.0f, 10.0f);
	std::cout << "Test 2: p2(10, 10) is inside? ";
	if (bsp(a, b, c, p2))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;

	// Test 3: Point on the edge (should be False per subject)
	Point const p3(5.0f, 0.0f);
	std::cout << "Test 3: p3(5, 0) [On the Edge] is inside? ";
	if (bsp(a, b, c, p3))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;

	// Test 4: Point on the vertex (should be False per subject)
	Point const p4(0.0f, 0.0f);
	std::cout << "Test 4: p4(0, 0) [On the Vertex] is inside? ";
	if (bsp(a, b, c, p4))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;

	// Test 5: Another triangle with negative coordinates
	Point const d(-5.0f, -5.0f);
	Point const e(5.0f, -5.0f);
	Point const f(0.0f, 5.0f);
	Point const p5(0.0f, 0.0f); // Origin point at the center of the triangle d, e, f
	std::cout << "Test 5: p5(0, 0) in triangles d,e,f is inside? ";
	if (bsp(d, e, f, p5))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;

	return (0);
}

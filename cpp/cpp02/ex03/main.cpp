#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	// 삼각형 구성: a(0, 0), b(10, 0), c(0, 10)
	Point const a(0.0f, 0.0f);
	Point const b(10.0f, 0.0f);
	Point const c(0.0f, 10.0f);

	std::cout << "========== BSP Test ==========" << std::endl;

	// 테스트 1: 삼각형 완전히 내부에 있는 점
	Point const p1(2.0f, 2.0f);
	std::cout << "Test 1: p1(2, 2) is inside? ";
	if (bsp(a, b, c, p1))
		std::cout << "\033[32mTrue\033[0m" << std::endl;
	else
		std::cout << "\033[31mFalse\033[0m" << std::endl;

	// 테스트 2: 삼각형 외부 (오른쪽 위)에 있는 점
	Point const p2(10.0f, 10.0f);
	std::cout << "Test 2: p2(10, 10) is inside? ";
	if (bsp(a, b, c, p2))
		std::cout << "\033[32mTrue\033[0m" << std::endl;
	else
		std::cout << "\033[31mFalse\033[0m" << std::endl;

	// 테스트 3: 변 (Edge) 위에 있는 점 -- 스펙상 False여야 함
	Point const p3(5.0f, 0.0f);
	std::cout << "Test 3: p3(5, 0) [On the Edge] is inside? ";
	if (bsp(a, b, c, p3))
		std::cout << "\033[32mTrue\033[0m" << std::endl;
	else
		std::cout << "\033[31mFalse\033[0m" << std::endl;

	// 테스트 4: 꼭짓점 (Vertex) 위에 있는 점 -- 스펙상 False여야 함
	Point const p4(0.0f, 0.0f);
	std::cout << "Test 4: p4(0, 0) [On the Vertex] is inside? ";
	if (bsp(a, b, c, p4))
		std::cout << "\033[32mTrue\033[0m" << std::endl;
	else
		std::cout << "\033[31mFalse\033[0m" << std::endl;

	// 테스트 5: 음수 좌표를 포함한 다른 삼각형 테스트
	Point const d(-5.0f, -5.0f);
	Point const e(5.0f, -5.0f);
	Point const f(0.0f, 5.0f);
	Point const p5(0.0f, 0.0f); // 원점이 d,e,f 삼각형 정중앙
	std::cout << "Test 5: p5(0, 0) in triangles d,e,f is inside? ";
	if (bsp(d, e, f, p5))
		std::cout << "\033[32mTrue\033[0m" << std::endl;
	else
		std::cout << "\033[31mFalse\033[0m" << std::endl;

	return 0;
}

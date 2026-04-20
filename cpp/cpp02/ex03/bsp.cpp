#include "Point.hpp"

// 외적 계산용 보조 함수
// 두 벡터 A, B의 외적(Cross Product)을 2차원 평면에서 구하는 보조 함수.
// 결과값이 양수/음수인지에 따라 회전 방향(좌/우)을 알 수 있음.
// 외적 공식: (x1 * y2) - (y1 * x2)
// p1을 기준점으로 하여 두 벡터 (p2 - p1)와 (p3 - p1)의 외적 Z 성분을 계산.
static Fixed getCrossProduct(Point const p1, Point const p2, Point const p3)
{
	// 벡터 1: p1 -> p2 (즉, p2 - p1)
	Fixed v1_x = p2.getX() - p1.getX();
	Fixed v1_y = p2.getY() - p1.getY();

	// 벡터 2: p1 -> p3 (즉, p3 - p1)
	Fixed v2_x = p3.getX() - p1.getX();
	Fixed v2_y = p3.getY() - p1.getY();

	// 외적 Z 성분 반환: v1.x * v2.y - v1.y * v2.x
	// ex02에서 만든 산술 연산자(*, -)가 정확하게 작동해야 올바른 값이 도출됨.
	return ((v1_x * v2_y) - (v1_y * v2_x));
}

// bsp 알고리즘: Binary Space Partitioning을 활용해 점이 삼각형 내부에 있는지 확인
// 점이 삼각형 [a,b,c] 내부에 있으면 true, 경계선이나 외부에 있으면 false 반환.
bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	// 삼각형의 세 변(선분)에 대해 점 point와의 외적 계산
	// 1. 선분 AB와 점 point
	Fixed cp1 = getCrossProduct(a, b, point);
	// 2. 선분 BC와 점 point
	Fixed cp2 = getCrossProduct(b, c, point);
	// 3. 선분 CA와 점 point
	Fixed cp3 = getCrossProduct(c, a, point);

	// 세 외적 결과의 부호가 모두 같은지 확인
	// 모두 양수(+)이거나 모두 음수(-)인 경우, 점은 모든 변의 같은 방향(내부)에 존재함.
	// 외적 결과가 단 하나라도 0이면, 점이 삼각형의 변 위(Edge) 또는 꼭짓점(Vertex)에 있는 것이므로 false 처리됨.
	if ((cp1 > Fixed(0) && cp2 > Fixed(0) && cp3 > Fixed(0)) ||
		(cp1 < Fixed(0) && cp2 < Fixed(0) && cp3 < Fixed(0)))
	{
		return (true);
	}

	return (false);
}

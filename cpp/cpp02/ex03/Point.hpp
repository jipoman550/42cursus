#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
	private:
		// 내부적으로 좌표를 고정 소수점으로 관리
		// 서브젝트 요구사항: x와 y는 상수(const)여야 함
		Fixed const x;
		Fixed const y;

	public:
		// ============================================================
		// Orthodox Canonical Class Form (정통 표준 클래스 형태)
		// ============================================================
		Point(); // 기본 생성자: x=0, y=0 으로 초기화
		Point(const Point &src); // 복사 생성자
		Point &operator=(const Point &rhs); // 복사 대입 연산자
		~Point(); // 소멸자

		// ============================================================
		// 추가 생성자 (ex03 요구사항)
		// ============================================================
		Point(const float x, const float y); // float 생성자

		// ============================================================
		// 멤버 함수 (Getter)
		// ============================================================
		// Point 객체의 x, y 값에 접근하기 위해 Getter 제공
		Fixed getX(void) const;
		Fixed getY(void) const;
};

#endif

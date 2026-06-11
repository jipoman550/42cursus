#ifndef BASE_HPP
#define BASE_HPP

/**
 * @brief 다형성을 지원하는 기반(Base) 클래스
 * RTTI 및 dynamic_cast의 정상적인 동작을 위해서는
 * 반드시 하나 이상의 가상 함수가 필요하므로 가상 소멸자를 선언합니다.
 */
class Base {
public:
	virtual ~Base() {}
};

#endif
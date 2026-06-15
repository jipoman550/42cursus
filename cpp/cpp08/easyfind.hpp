#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

// 값을 찾지 못했을 때 던질 커스텀 예외 클래스
class ValueNotFoundException : public std::exception {
public:
	// C++98 표준에 맞게 예외 지정자(throw()) 사용
	virtual const char* what() const throw()
	{
		return ("Error: Value not found in the container.");
	}
};

/**
 * @brief 컨테이너 T에서 첫 번째로 등장하는 정수 value를 찾는 템플릿 함수
 *
 * @tparam T 정수를 저장하는 컨테이너 타입 (예: std::vector<int>)
 * @param container 검색할 컨테이너 참조
 * @param value 찾고자 하는 정수 값
 * @return typename T::iterator 값을 찾은 위치를 가리키는 반복자
 */
template <typename T>
typename T::iterator easyfind(T& container, int value)
{
	// std::find를 활용하여 컨테이너 내에서 값 탐색
	typename T::iterator it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
	{
		throw ValueNotFoundException();
	}
	return (it);
}

#endif
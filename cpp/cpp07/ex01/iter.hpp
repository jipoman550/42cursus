#ifndef ITER_HPP
# define ITER_HPP

# include <cstddef>

/*
 * iter 템플릿 함수
 * - 첫 번째 인자: 배열의 주소 (포인터)
 * - 두 번째 인자: 배열의 길이 (std::size_t)
 * - 세 번째 인자: 각 요소에 호출할 함수 (typename F)
 *
 * 세 번째 인자의 타입을 명시적으로 지정(void (*)(T&), void (*)(const T&) 등)하지 않고,
 * 템플릿 타입 F로 유추하게 만들면 일반 함수, const 참조 인자를 받는 함수,
 * 더 나아가 함수 객체(Functor)까지 문제없이 호출할 수 있어 완벽한 유연성과 const 안전성을 갖춥니다.
 */
template <typename T, typename F>
void iter(T* array, std::size_t length, F func)
{
	for (std::size_t i = 0; i < length; ++i)
	{
		func(array[i]);
	}
}

#endif
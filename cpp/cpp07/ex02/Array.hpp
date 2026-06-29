#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>

template <typename T>
class Array
{
private:
	T*				_array;
	unsigned int	_size;

public:
	// 기본 생성자
	Array();
	// 인자를 받는 생성자
	Array(unsigned int n);
	// 복사 생성자
	Array(const Array& other);
	// 소멸자
	~Array();

	// 복사 대입 연산자
	Array& operator=(const Array& other);

	// 첨자 연산자 오버로딩 (일반 및 const)
	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;

	// size 함수
	unsigned int size() const;

	// 예외 클래스
	class OutOfBoundsException;
};

# include "Array.tpp"
#endif
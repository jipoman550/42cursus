#ifndef ARRAY_TPP
# define ARRAY_TPP

# include "Array.hpp"
# include <cstddef>

// 빈 배열 초기화 (NULL 포인터와 0 크기)
template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {}

// n개의 원소를 가지며, 기본값으로 초기화된 배열 생성
template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {}

// 복사 생성자 (깊은 복사 수행)
template <typename T>
Array<T>::Array(const Array<T>& other) : _array(NULL), _size(other._size)
{
	if (_size > 0)
	{
		_array = new T[_size]();
		for (unsigned int i = 0; i < _size; ++i)
		{
			_array[i] = other._array[i];
		}
	}
}

// 소멸자 (메모리 해제)
template <typename T>
Array<T>::~Array()
{
	if (_array)
	{
		delete[] _array;
	}
}

// 복사 대입 연산자 (자기 참조 확인 및 깊은 복사 수행)
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		if (_array)
		{
			delete[] _array;
		}
		_size = other._size;
		if (_size > 0)
		{
			_array = new T[_size]();
			for (unsigned int i = 0; i < _size; ++i)
			{
				_array[i] = other._array[i];
			}
		}
		else
		{
			_array = NULL;
		}
	}
	return (*this);
}

// 범위 검사를 포함하는 첨자 연산자
template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
	{
		throw OutOfBoundsException();
	}
	return (_array[index]);
}

// const 객체를 위한 읽기 전용 첨자 연산자
template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
	{
		throw OutOfBoundsException();
	}
	return (_array[index]);
}

// 배열의 크기 반환
template <typename T>
unsigned int Array<T>::size() const
{
	return (_size);
}

template <typename T>
class Array<T>::OutOfBoundsException : public std::exception
{
public:
	virtual const char* what() const throw() { return ("Index is out of bounds."); }
};

#endif
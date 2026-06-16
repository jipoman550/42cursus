#include "Span.hpp"
#include <algorithm>

// 기본 생성자
Span::Span() : _maxSize(0) {}

// 오버로딩된 생성자 (크기 지정)
Span::Span(unsigned int n) : _maxSize(n) {}

// 복사 생성자
Span::Span(const Span& other) : _maxSize(other._maxSize), _vec(other._vec) {}

// 복사 대입 연산자
Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_vec = other._vec;
	}
	return (*this);
}

// 소멸자
Span::~Span() {}

// 단일 숫자 추가
void Span::addNumber(int number)
{
	if (_vec.size() >= _maxSize)
	{
		throw FullSpanException();
	}
	_vec.push_back(number);
}

// 가장 짧은 거리(Span) 반환
unsigned int Span::shortestSpan()
{
	if (_vec.size() <= 1)
	{
		throw NoSpanException();
	}

	// 기존 벡터의 원본 순서를 유지하기 위해 복사 후 정렬 수행
	std::vector<int> sortedVec = _vec;
	std::sort(sortedVec.begin(), sortedVec.end());

	// 최대 unsigned int 값(-1을 unsigned int로 캐스팅)으로 초기화
	unsigned int minSpan = static_cast<unsigned int>(-1);

	// 인접한 원소들 간의 차이를 순회하며 최소값을 갱신
	for (size_t i = 1; i < sortedVec.size(); ++i)
	{
		unsigned int span = static_cast<unsigned int>(sortedVec[i]) - static_cast<unsigned int>(sortedVec[i - 1]);
		if (span < minSpan)
		{
			minSpan = span;
		}
	}
	return (minSpan);
}

// 가장 긴 거리(Span) 반환
unsigned int Span::longestSpan()
{
	if (_vec.size() <= 1)
	{
		throw NoSpanException();
	}

	// 정렬 없이 최솟값과 최댓값을 찾는 알고리즘 사용
	int minVal = *std::min_element(_vec.begin(), _vec.end());
	int maxVal = *std::max_element(_vec.begin(), _vec.end());

	// 차이를 unsigned int로 반환 (음수와 양수 사이의 거리 연산에서의 오버플로우 방지)
	return (static_cast<unsigned int>(maxVal) - static_cast<unsigned int>(minVal));
}

// 예외 처리 메시지 반환 함수
const char* Span::FullSpanException::what() const throw()
{
	return ("Error: Span is full. Cannot add more numbers.");
}

const char* Span::NoSpanException::what() const throw()
{
	return ("Error: Not enough numbers to find a span.");
}

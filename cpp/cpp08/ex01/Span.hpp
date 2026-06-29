#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <iterator>
#include <algorithm>

// 최대 N개의 정수를 보관하는 클래스
class Span {
private:
	unsigned int		_maxSize;
	std::vector<int>	_vec;

public:
	// Orthodox Canonical Form
	Span();
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	// 멤버 함수
	void addNumber(int number);
	unsigned int shortestSpan();
	unsigned int longestSpan();

	// 범위 기반 추가 템플릿 함수 (구현은 템플릿 특성상 헤더에 포함)
	template <typename InputIterator>
	void addNumbers(InputIterator first, InputIterator last)
	{
		unsigned int distance = std::distance(first, last);
		// 넣으려는 데이터 개수와 남은 용량 비교
		if (distance > _maxSize - _vec.size())
		{
			throw FullSpanException();
		}
		// vector의 insert 함수를 활용한 최적화된 범위 삽입
		_vec.insert(_vec.end(), first, last);
	}

	// 커스텀 예외 클래스 (C++98 예외 지정자 포함)
	class FullSpanException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class NoSpanException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
};

#endif

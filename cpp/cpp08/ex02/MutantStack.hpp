#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>

/**
 * @brief std::stack을 상속받아 반복자(Iterator) 기능을 제공하는 돌연변이 스택
 *
 * @tparam T 스택에 저장할 데이터 타입
 */
template <typename T>
class MutantStack : public std::stack<T> {
public:
	// Orthodox Canonical Form (OCCF) 준수
	MutantStack() : std::stack<T>() {}
	MutantStack(const MutantStack& other) : std::stack<T>(other) {}

	MutantStack& operator=(const MutantStack& other)
	{
		if (this != &other)
		{
			// 부모 클래스의 복사 대입 연산자 호출
			std::stack<T>::operator=(other);
		}
		return (*this);
	}

	~MutantStack() {}

	// 부모 클래스인 std::stack의 container_type을 이용해 반복자 타입 정의
	// 컴파일러에게 명확한 타입을 알려주기 위해 typename 키워드 필수 사용
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

	// 내부 컨테이너(c)의 반복자를 반환하는 멤버 함수 구현
	// 템플릿 상속 관계에서 부모의 멤버에 접근할 때 this-> 를 붙여 모호성 해결
	iterator begin() { return (this->c.begin()); }
	iterator end() { return (this->c.end()); }

	const_iterator begin() const { return (this->c.begin()); }
	const_iterator end() const { return (this->c.end()); }

	reverse_iterator rbegin() { return (this->c.rbegin()); }
	reverse_iterator rend() { return (this->c.rend()); }

	const_reverse_iterator rbegin() const { return (this->c.rbegin()); }
	const_reverse_iterator rend() const { return (this->c.rend()); }
};

#endif

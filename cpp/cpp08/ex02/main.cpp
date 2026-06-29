#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main()
{
	std::cout << "========== [ 1. Subject Test (MutantStack) ] ==========" << std::endl;
	{
		// 과제 PDF에 제시된 기본 테스트 코드
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << mstack.top() << std::endl; // 17 출력

		mstack.pop();

		std::cout << mstack.size() << std::endl; // 1 출력 (5만 남음)

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl; // 5, 3, 5, 737, 0 순서로 출력
			++it;
		}
		std::stack<int> s(mstack); // 복사 생성자 테스트
	}

	std::cout << "\n========== [ 2. Subject Test (std::list Comparison) ] ==========" << std::endl;
	{
		// MutantStack과 동일한 동작을 하는지 검증하기 위한 std::list 테스트
		std::list<int> mstack;

		mstack.push_back(5);
		mstack.push_back(17);

		std::cout << mstack.back() << std::endl; // top() -> back()

		mstack.pop_back(); // pop() -> pop_back()

		std::cout << mstack.size() << std::endl;

		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		//[...]
		mstack.push_back(0);

		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::list<int> s(mstack);
	}

	std::cout << "\n========== [ 3. Extended Iterators Test ] ==========" << std::endl;
	{
		MutantStack<int> mstack;
		for (int i = 1; i <= 5; ++i)
			mstack.push(i * 10); // 10, 20, 30, 40, 50 추가

		// reverse_iterator 역방향 순회 테스트
		std::cout << "[ reverse_iterator ]" << std::endl;
		MutantStack<int>::reverse_iterator rit = mstack.rbegin();
		MutantStack<int>::reverse_iterator rite = mstack.rend();
		for (; rit != rite; ++rit)
		{
			std::cout << *rit << " "; // 50, 40, 30, 20, 10
		}
		std::cout << std::endl;

		// const_iterator 상수 반복자 순회 테스트
		std::cout << "\n[ const_iterator ]" << std::endl;
		const MutantStack<int> const_mstack = mstack;

		// 1. for문 밖에서 미리 선언 및 초기화
		MutantStack<int>::const_iterator cit = const_mstack.begin();
		MutantStack<int>::const_iterator cite = const_mstack.end();

		// 2. 초기식 자리를 비워두고 세미콜론만 배치
		for (; cit != cite; ++cit)
		{
			std::cout << *cit << " "; // 10, 20, 30, 40, 50
		}
		std::cout << std::endl;
	}

	return (0);
}

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception> // std::exception 사용

/**
 * @brief A, B, C 중 하나를 무작위로 동적 할당하여 반환합니다.
 */
Base* generate(void)
{
	int randVal = std::rand() % 3;

	if (randVal == 0)
	{
		return (new A());
	}
	else if (randVal == 1)
	{
		return (new B());
	}
	else
	{
		return (new C());
	}
}

/**
 * @brief 포인터를 이용한 동적 타입 식별
 * 포인터 버전은 dynamic_cast 실패 시 NULL을 반환하는 특성을 이용합니다.
 */
void identify(Base* p)
{
	std::cout << "[Pointer]   Real type is : ";

	if (p == NULL)
	{
		std::cout << "NULL" << std::endl;
		return ;
	}

	if (dynamic_cast<A*>(p) != NULL)
	{
		std::cout << "A" << std::endl;
	}
	else if (dynamic_cast<B*>(p) != NULL)
	{
		std::cout << "B" << std::endl;
	}
	else if (dynamic_cast<C*>(p) != NULL)
	{
		std::cout << "C" << std::endl;
	}
	else
	{
		std::cout << "Unknown" << std::endl;
	}
}

/**
 * @brief 참조자를 이용한 동적 타입 식별
 * 참조자 버전은 포인터와 달리 NULL이 없으므로 실패 시 bad_cast 예외를 던집니다.
 * <typeinfo> 헤더 사용이 금지되어 있으므로 상위 예외인 std::exception을 캐치하여 검사합니다.
 */
void identify(Base& p)
{
	std::cout << "[Reference] Real type is : ";

	try
	{
		// 성공하면 아무 일도 안 일어나고 다음 줄이 실행됩니다.
		dynamic_cast<A&>(p); //(void)
		std::cout << "A" << std::endl;
		return ; // 성공하면 즉시 함수 종료
	}
	catch (const std::exception& e)
	{
		// 실패하면 아무 동작도 하지 않고 다음 블록으로 넘어감
	}

	try
	{
		dynamic_cast<B&>(p); //(void)
		std::cout << "B" << std::endl;
		return ;
	}
	catch (const std::exception& e)
	{
	}

	try
	{
		dynamic_cast<C&>(p); //(void)
		std::cout << "C" << std::endl;
		return ;
	}
	catch (const std::exception& e)
	{
	}

	// 셋 다 실패한 경우
	std::cout << "Unknown" << std::endl;
}

int main()
{
	// 난수 발생기 초기화 (항상 매번 다른 결과를 얻기 위함)
	// 이 부분 좀 알아봐야할듯. static_cast<unsigned int> 이거는 왜 넣는건지.
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "================= [ RANDOM TEST ] =================" << std::endl;

	// 여러 번 랜덤 객체를 생성하며 테스트 수행
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "--- Test " << i + 1 << " ---" << std::endl;

		// 1. 랜덤 객체 생성
		Base* randomBase = generate();
		if (!randomBase)
		{
			std::cerr << "Memory allocation failed" << std::endl;
			return (1);
		}

		// 2. 식별 로직 검증 (포인터와 참조자)
		identify(randomBase);
		identify(*randomBase);

		// 3. 메모리 누수 방지 처리
		delete randomBase;
		std::cout << std::endl;
	}

	std::cout << "===================================================" << std::endl;

	std::cout << sizeof(Base) << std::endl;
	std::cout << sizeof(A) << std::endl;
	std::cout << sizeof(B) << std::endl;
	std::cout << sizeof(C) << std::endl;

	return (0);
}
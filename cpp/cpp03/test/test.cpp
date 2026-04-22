#include <iostream>
#include <string>

class Base
{
	public:
		Base() { std::cout << "Base 생성자" << std::endl; }
		// virtual이 없는 경우 vs 있는 경우
		~Base() { std::cout << "Base 소멸자" << std::endl; }
		//virtual ~Base() { std::cout << "Base 소멸자" << std::endl; }
};

class Derived : public Base
{
	private:
		int* _data;
	public:
		Derived() : _data(new int[10]) { std::cout << "Derived 생성자" << std::endl; }
		virtual ~Derived()
		{
			delete[] _data; // 이 부분이 실행되어야 메모리 누수가 안 생김!
			std::cout << "Derived 소멸자" << std::endl;
		}
};

int main()
{
	Base* ptr = new Derived();
	std::cout << "--- 객체 삭제 시작 ---" << std::endl;
	delete ptr;
	return (0);
}

// compile: c++ -Wall -Wextra -Werror -std=c++98 test.cpp -o test_exec

// ============== virtual 없는 경우 (~Base()) ================

/*> valgrind --leak-check=full ./test_exec
==1158212== Memcheck, a memory error detector
==1158212== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1158212== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1158212== Command: ./test_exec
==1158212==
Base 생성자
Derived 생성자
--- 객체 삭제 시작 ---
Base 소멸자
==1158212==
==1158212== HEAP SUMMARY:
==1158212==     in use at exit: 40 bytes in 1 blocks
==1158212==   total heap usage: 4 allocs, 3 frees, 73,776 bytes allocated
==1158212==
==1158212== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==1158212==    at 0x484A2F3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1158212==    by 0x1093EA: Derived::Derived() (in /home/sisung/workspace/42cursus/cpp/cpp03/test/test_exec)
==1158212==    by 0x10924C: main (in /home/sisung/workspace/42cursus/cpp/cpp03/test/test_exec)
==1158212==
==1158212== LEAK SUMMARY:
==1158212==    definitely lost: 40 bytes in 1 blocks
==1158212==    indirectly lost: 0 bytes in 0 blocks
==1158212==      possibly lost: 0 bytes in 0 blocks
==1158212==    still reachable: 0 bytes in 0 blocks
==1158212==         suppressed: 0 bytes in 0 blocks
==1158212==
==1158212== For lists of detected and suppressed errors, rerun with: -s
==1158212== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)*/

// ============== virtual 있는 경우 (virtual ~Base()) ================

/*> valgrind --leak-check=full ./test_exec
==1158388== Memcheck, a memory error detector
==1158388== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1158388== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1158388== Command: ./test_exec
==1158388==
Base 생성자
Derived 생성자
--- 객체 삭제 시작 ---
Derived 소멸자
Base 소멸자
==1158388==
==1158388== HEAP SUMMARY:
==1158388==     in use at exit: 0 bytes in 0 blocks
==1158388==   total heap usage: 4 allocs, 4 frees, 73,784 bytes allocated
==1158388==
==1158388== All heap blocks were freed -- no leaks are possible
==1158388==
==1158388== For lists of detected and suppressed errors, rerun with: -s
==1158388== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)*/
#include "PmergeMe.hpp"
#include <iostream>

/**
 * @brief 프로그램의 메인 진입점.
 * @details 프로그램 실행 시 인자로 양의 정수 시퀀스를 받아 PmergeMe 클래스를 통해 정렬을 수행합니다.
 * @param argc 인자의 개수.
 * @param argv 인자 배열. argv[1]부터 정수 시퀀스가 시작됩니다.
 * @return 성공 시 0, 오류 발생 시 1을 반환합니다.
 */
int main(int argc, char **argv)
{
	// 프로그램 실행 시 인자의 개수를 확인합니다.
	// 실행 파일 이름(argv[0]) 외에 최소 하나 이상의 정수가 필요합니다.
	if (argc < 2)
	{
		// 인자가 부족하면 표준 에러(std::cerr)에 에러 메시지를 출력합니다.
		std::cerr << "Error: Not enough arguments." << std::endl;
		std::cerr << "Usage: ./PmergeMe [positive integer sequence]" << std::endl;
		// 비정상 종료를 의미하는 1을 반환하며 프로그램을 종료합니다.
		return (1);
	}

	// 예외 처리를 위한 try-catch 블록입니다.
	// PmergeMe 처리 중 발생할 수 있는 모든 예외(파싱 오류 등)를 감지합니다.
	try
	{
		// PmergeMe의 정적 멤버 함수를 호출하여 전체 프로세스를 시작합니다.
		PmergeMe::process(argc, argv);
	}
	catch (const std::exception& e)
	{
		// 예외 객체의 what() 메서드를 호출하여 에러 메시지("Error")를 표준 에러에 출력합니다.
		std::cerr << e.what() << std::endl;
		// 비정상 종료를 의미하는 1을 반환합니다.
		return (1);
	}

	// 모든 작업이 성공적으로 완료되면 0을 반환하며 프로그램을 정상 종료합니다.
	return (0);
}

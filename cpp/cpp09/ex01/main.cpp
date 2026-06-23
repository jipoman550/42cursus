#include "RPN.hpp"
#include <iostream>

/**
 * @brief 프로그램의 메인 진입점.
 * @details 프로그램 실행 시 하나의 인자(RPN 수식 문자열)를 받아 RPN 클래스를 통해 계산을 수행합니다.
 * @param argc 인자의 개수.
 * @param argv 인자 배열. argv[1]에 RPN 수식이 있어야 합니다.
 * @return 성공 시 0, 오류 발생 시 1을 반환합니다.
 */
int main(int argc, char **argv)
{
	// 프로그램 실행 시 인자의 개수를 확인합니다.
	// 실행 파일 이름(argv[0])과 RPN 수식(argv[1]), 총 2개가 필요합니다.
	if (argc != 2)
	{
		// 인자의 개수가 올바르지 않으면 표준 에러(std::cerr)에 에러 메시지를 출력합니다.
		std::cerr << "Error" << std::endl;
		// 비정상 종료를 의미하는 1을 반환하며 프로그램을 종료합니다.
		return (1);
	}

	// 예외 처리를 위한 try-catch 블록입니다.
	// RPN 계산 중 발생할 수 있는 모든 예외를 감지합니다.
	try
	{
		RPN rpn;
		// calculate 멤버 함수를 호출하여 인자로 받은 RPN 수식의 계산을 시작합니다.
		rpn.calculate(argv[1]);
	}
	catch (const std::exception& e)
	{
		// 예외 객체의 what() 메서드를 호출하여 에러 메시지("Error")를 표준 에러에 출력합니다.
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
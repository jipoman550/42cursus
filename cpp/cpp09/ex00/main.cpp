#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	// 프로그램 실행 시 인자의 개수를 확인합니다.
	// 실행 파일 이름(argv[0])과 입력 파일 경로(argv[1]), 총 2개가 필요합니다.
	if (argc != 2)
	{
		// 인자의 개수가 올바르지 않으면 표준 에러(std::cerr)에 에러 메시지를 출력합니다.
		std::cerr << "Error: could not open file." << std::endl;
		// 비정상 종료를 의미하는 1을 반환하며 프로그램을 종료합니다.
		return (1);
	}

	// 예외 처리를 위한 try-catch 블록입니다.
	// BitcoinExchange 객체 생성 또는 실행 중 발생할 수 있는 예외를 감지합니다.
	try
	{
		// BitcoinExchange 클래스의 인스턴스(객체)를 생성합니다.
		// 이 때, 기본 생성자가 호출되어 "data.csv" 파일을 자동으로 로드합니다.
		BitcoinExchange btc;
		// execute 멤버 함수를 호출하여 인자로 받은 입력 파일(argv[1])의 처리를 시작합니다.
		btc.execute(argv[1]);
	}
	// try 블록 내에서 std::exception을 상속받는 예외가 발생하면 catch 블록이 실행됩니다.
	// 저희가 정의한 FileOpenException도 여기에 해당됩니다.
	catch (const std::exception& e)
	{
		// 예외 객체의 what() 메서드를 호출하여 에러 메시지를 표준 에러에 출력합니다.
		std::cerr << e.what() << std::endl;
		// 비정상 종료를 의미하는 1을 반환합니다.
		return (1);
	}

	// 모든 작업이 성공적으로 완료되면 0을 반환하며 프로그램을 정상 종료합니다.
	return (0);
}

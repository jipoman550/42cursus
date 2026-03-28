#include "Harl.hpp"
#include <iostream>

// main 함수: 프로그램의 시작점
int main(int argc, char *argv[])
{
	// 인자의 개수가 2개가 아닌 경우 (프로그램 이름 + 레벨)
	if (argc != 2)
	{
		// 사용법 안내 메시지 출력
		std::cout << "Usage: " << argv[0] << " <LEVEL>" << std::endl;
		// 프로그램 비정상 종료 (오류 코드 1)
		return (1);
	}

	// Harl 클래스의 인스턴스 생성
	Harl harl;
	// 입력받은 로그 레벨을 문자열로 저장
	std::string level = argv[1];
	// 로그 레벨을 담고 있는 문자열 배열
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	// 입력받은 레벨이 어느 인덱스에 해당하는지 찾기 위한 변수
	int i = 0;
	// levels 배열을 순회하며 일치하는 레벨을 찾음
	while (i < 4 && levels[i].compare(level))
	{
		i++;
	}

	// switch 문을 사용하여 입력된 레벨에 따라 분기
	switch (i)
	{
		// "DEBUG" 레벨일 경우
		case 0:
			// DEBUG 레벨의 complain 메시지 출력
			harl.complain("DEBUG");
			// 의도적으로 break를 생략하여 아래 case로 넘어감 (fall-through)
		// "INFO" 레벨일 경우
		case 1:
			// INFO 레벨의 complain 메시지 출력
			harl.complain("INFO");
			// 의도적으로 break를 생략하여 아래 case로 넘어감 (fall-through)
		// "WARNING" 레벨일 경우
		case 2:
			// WARNING 레벨의 complain 메시지 출력
			harl.complain("WARNING");
			// 의도적으로 break를 생략하여 아래 case로 넘어감 (fall-through)
		// "ERROR" 레벨일 경우
		case 3:
			// ERROR 레벨의 complain 메시지 출력
			harl.complain("ERROR");
			// switch 문 종료
			break ;
		// 정의되지 않은 레벨일 경우
		default:
			// 기본 메시지 출력
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
	}
	// 프로그램 정상 종료
	return (0);
}
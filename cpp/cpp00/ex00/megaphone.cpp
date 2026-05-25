#include <cctype>
#include <iostream>

int main(int argc, char *argv[])
{
	// 1. argc가 1이면 특정 노이즈 출력 후 종료
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (1);
	}
	else
	{
		// 2. argc가 2 이상이면 루프 시작 (i = 1부터 argc 미만까지)
		for (int i = 1; i < argc; ++i)
		{
			// 2-a. argv[i] 문자열의 각 문자를 하나씩 확인하는 내부 루프
			for (int j = 0; argv[i][j] != '\0'; ++j)
			{
				// 2-a-1. 문자를 std::toupper()로 변환
				// 2-a-2. std::cout을 이용해 변환된 문자 출력
				std::cout << (char)std::toupper((unsigned char)argv[i][j]);
			}
		}
		// 3. 모든 루프가 끝나면 std::endl로 줄바꿈 출력
		std::cout << std::endl;
	}

	return (0);
}
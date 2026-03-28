#include <iostream> // 표준 입출력 스트림 (cout, cerr)
#include <fstream>  // 파일 스트림 (ifstream, ofstream)
#include <string>   // C++ 문자열 클래스
#include <sstream>  // 문자열 스트림 (stringstream)

// 파일 내용을 읽고, 특정 문자열을 다른 문자열로 교체하여 새 파일에 쓰는 함수
void replaceInFile(const std::string& filename, const std::string& s1, const std::string& s2)
{
	// --- 1. 입력 파일 열기 및 오류 처리 ---
	// std::ifstream: 파일로부터 데이터를 읽기 위한 클래스
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: Could not open input file '" << filename << "'" << std::endl;
		return ;
	}

	// --- 2. 파일 내용 전체를 문자열로 읽기 ---
	// std::stringstream: 문자열을 스트림처럼 다루게 해주는 클래스.
	// rdbuf()를 이용해 파일 버퍼의 모든 내용을 한번에 읽어들입니다.
	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	std::string content = buffer.str();
	inputFile.close(); // 파일 핸들러를 닫습니다.

	// --- 3. 문자열 치환 로직 (std::string::replace 없이) ---
	std::string result = "";
	// s1과 s2가 같다면 치환 작업이 무의미하므로 원본 내용을 그대로 사용합니다.
	if (s1 == s2)
	{
		result = content;
	}
	else
	{
		size_t lastPos = 0;
		size_t findPos;
		// content.find(s1, lastPos): lastPos 위치부터 s1을 검색합니다.
		// 찾지 못하면 std::string::npos를 반환합니다.
		while ((findPos = content.find(s1, lastPos)) != std::string::npos)
		{
			// 마지막 검색 위치(lastPos)부터 s1을 찾은 위치(findPos)까지의 문자열을 결과에 추가합니다.
			result.append(content.substr(lastPos, findPos - lastPos));
			// 찾은 s1 대신 s2를 결과에 추가합니다.
			result.append(s2);
			// 다음 검색 시작 위치를 현재 찾은 s1의 끝으로 업데이트합니다.
			lastPos = findPos + s1.length();
		}
		// 마지막으로 찾은 s1 이후의 남은 문자열을 결과에 추가합니다.
		result.append(content.substr(lastPos));
	}


	// --- 4. 결과 파일 쓰기 ---
	std::string outputFilename = filename + ".replace";
	// std::ofstream: 파일에 데이터를 쓰기 위한 클래스
	std::ofstream outputFile(outputFilename.c_str());
	if (!outputFile.is_open())
	{
		std::cerr << "Error: Could not create output file '" << outputFilename << "'" << std::endl;
		return ;
	}

	outputFile << result;	// 결과 문자열을 파일에 씁니다.
	outputFile.close();		// 파일 핸들러를 닫습니다.
}

int main(int argc, char **argv)
{
	// --- 인자 개수 유효성 검사 ---
	// 프로그램 실행 시 필요한 인자는 총 3개(파일명, s1, s2)입니다.
	// argc는 프로그램 이름까지 포함하므로 4가 되어야 합니다.
	if (argc != 4)
	{
		std::cerr << "Error: Invalid number of arguments." << std::endl;
		std::cerr << "Usage: ./sed_is_for_losers <filename> <s1> <s2>" << std::endl;
		return (1);
	}

	// --- 인자 저장 및 엣지 케이스 처리 ---
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	// 파일명이나 찾을 문자열(s1)이 비어있으면 작업이 불가능하므로 에러 처리합니다.
	if (filename.empty())
	{
		std::cerr << "Error: Filename cannot be empty." << std::endl;
		return (1);
	}
	if (s1.empty())
	{
		std::cerr << "Error: The string to be replaced (s1) cannot be empty." << std::endl;
		return (1);
	}

	// 핵심 로직을 수행하는 함수 호출
	replaceInFile(filename, s1, s2);

	return (0);
}

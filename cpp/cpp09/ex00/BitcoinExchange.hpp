#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <stdexcept>

/**
 * @brief BitcoinExchange 클래스는 비트코인 환율 데이터를 관리하고,
 *        입력 파일(예: input.txt)에 포함된 날짜 및 수량에 맞춰 환율을 계산하는 기능을 제공합니다.
 */
class BitcoinExchange {
private:
	// 데이터베이스(data.csv) 파일에서 파싱한 날짜(std::string)와 환율(float)을 저장하는 컨테이너
	std::map<std::string, float> _data;

	// Private helper methods
	// 데이터베이스 파일을 열고 읽어서 _data 맵에 저장하는 함수
	void loadDatabase(const std::string& dbPath);
	// 입력 파일의 각 줄을 파싱하여 값을 검증하고, 환율을 계산하여 결과를 출력하거나 에러를 처리하는 함수
	void processInputLine(const std::string& line);
	// 주어진 날짜 문자열이 유효한 YYYY-MM-DD 형식이며, 달력상 존재하는 날짜(윤년 포함)인지 검증하는 함수
	bool validateDate(const std::string& date) const;
	// 입력된 날짜와 일치하는 환율을 찾거나, 정확한 날짜가 없으면 가장 가까운 과거 날짜의 환율을 반환하는 함수
	float findRate(const std::string& date) const;
	// 문자열 양 끝의 공백(whitespace) 문자를 제거해주는 헬퍼 함수
	std::string trim(const std::string& str) const;

public:
	// Orthodox Canonical Form
	BitcoinExchange();                                      // 기본 생성자: 객체 생성 시 데이터베이스 자동 로드 시도
	BitcoinExchange(const BitcoinExchange& src);            // 복사 생성자
	BitcoinExchange& operator=(const BitcoinExchange& rhs); // 복사 대입 연산자
	~BitcoinExchange();                                     // 소멸자

	// Main execution function
	// 인자로 받은 입력 파일을 열어 첫 줄(헤더)을 건너뛰고, 한 줄씩 processInputLine에 넘겨 실행하는 핵심 퍼블릭 함수
	void execute(const std::string& inputFilename);

	// Custom exception class for file errors
	// 파일(데이터베이스 또는 입력 파일)을 열 수 없을 때 던질 예외 클래스
	class FileOpenException : public std::exception {
	public:
		virtual const char* what() const throw()
		{
			return ("Error: could not open file.");
		}
	};
};

#endif

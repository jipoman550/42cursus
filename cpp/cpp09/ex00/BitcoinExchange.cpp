#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cctype>

// --- Orthodox Canonical Form ---

/**
 * @brief 기본 생성자
 * @details "data.csv" 파일을 열어 데이터베이스를 로드합니다. 로드에 실패하면 예외를 던져 main에서 처리하도록 합니다.
 */
BitcoinExchange::BitcoinExchange()
{
	try
	{
		loadDatabase("data.csv");
	}
	catch (const std::exception& e)
	{
		// Rethrow to be handled in main
		throw ;
	}
}

/**
 * @brief 복사 생성자
 * @param src 복사할 원본 객체
 */
BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
}

/**
 * @brief 대입 연산자 오버로딩
 * @param rhs 대입할 우변 객체
 * @return 갱신된 현재 객체의 참조자
 */
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
	{
		this->_data = rhs._data;
	}
	return (*this);
}

/**
 * @brief 소멸자
 */
BitcoinExchange::~BitcoinExchange() {}

// --- Public Methods ---

/**
 * @brief 인자로 받은 입력 파일을 처리하는 메인 실행 함수
 * @param inputFilename 읽어들일 입력 파일의 경로
 * @throw FileOpenException 파일을 열 수 없을 경우 발생
 */
void BitcoinExchange::execute(const std::string& inputFilename)
{
	// 입력 파일 스트림 생성 및 열기 확인
	std::ifstream inputFile(inputFilename.c_str());
	if (!inputFile.is_open())
	{
		throw FileOpenException();
	}

	std::string line;

	// 첫 번째 줄(헤더 "date | value")은 데이터가 아니므로 읽고 건너뜁니다.
	std::getline(inputFile, line);

	// 파일의 끝까지 한 줄씩 읽어와서 파싱 및 처리 함수에 전달합니다.
	while (std::getline(inputFile, line))
	{
		processInputLine(line);
	}
}

// --- Private Helper Methods ---

/**
 * @brief 데이터베이스(CSV) 파일을 읽어 맵 컨테이너에 저장
 * @param dbPath 데이터베이스 파일 경로
 * @throw FileOpenException 파일을 열 수 없을 경우 발생
 */
void BitcoinExchange::loadDatabase(const std::string& dbPath)
{
	// 데이터베이스 파일 스트림 생성 및 열기 확인
	std::ifstream dbFile(dbPath.c_str());
	if (!dbFile.is_open())
	{
		throw FileOpenException();
	}

	std::string line;
	std::getline(dbFile, line); // 헤더 "date,exchange_rate" 라인을 읽어서 무시

	// 끝까지 한 줄씩 읽어 처리
	while (std::getline(dbFile, line))
	{
		// 쉼표(',')를 기준으로 날짜와 환율을 분리
		size_t commaPos = line.find(',');
		if (commaPos != std::string::npos)
		{
			// 날짜 문자열 추출
			std::string date = line.substr(0, commaPos);
			// 환율 문자열 추출
			std::string rateStr = line.substr(commaPos + 1);
			// 추출한 환율 문자열을 float으로 변환
			float rate = static_cast<float>(std::atof(rateStr.c_str()));
			// 맵 컨테이너에 저장
			_data[date] = rate;
		}
	}
}

/**
 * @brief 입력 파일의 단일 라인을 파싱하고 값을 검증하여 환율 결과를 계산 및 출력
 * @param line 파싱할 입력 파일의 한 줄 ("date | value" 형식)
 */
void BitcoinExchange::processInputLine(const std::string& line)
{
	// 파이프('|') 구분자의 위치를 찾습니다.
	size_t separatorPos = line.find('|');
	if (separatorPos == std::string::npos)
	{
		// 구분자가 없다면 형식이 잘못된 것이므로 에러 메시지를 출력합니다.
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}

	// 구분자를 기준으로 앞은 날짜, 뒤는 값으로 분리하고 양쪽 공백을 제거합니다.
	std::string dateStr = trim(line.substr(0, separatorPos));
	std::string valueStr = trim(line.substr(separatorPos + 1));

	// 파싱된 날짜나 값이 비어있거나, 날짜가 유효한 형식이 아니라면 에러 처리합니다.
	if (dateStr.empty() || valueStr.empty() || !validateDate(dateStr))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}

	// 값 문자열을 double형 실수로 변환합니다. (strtod를 사용해 변환 오류 검출 용이)
	char* endptr = NULL;
	double value = std::strtod(valueStr.c_str(), &endptr);

	// 변환된 숫자가 전혀 없는 경우 (숫자가 아닌 문자로만 이루어진 경우)
	if (endptr == valueStr.c_str())
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}

	// 숫자로 변환된 이후 뒤에 남은 문자가 있는지 확인합니다 (공백 문자는 허용)
	// 예를 들어 "3.5a" 같은 입력을 걸러내기 위함입니다.
	while (*endptr != '\0')
	{
		if (!std::isspace(static_cast<unsigned char>(*endptr)))
		{
			// 공백이 아닌 문자가 존재하면 에러 처리
			std::cout << "Error: bad input => " << line << std::endl;
			return ;
		}
		endptr++;
	}

	// 문제 요구사항: 값은 양수여야 합니다.
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return ;
	}
	// 문제 요구사항: 값은 1000 이하여야 합니다.
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return ;
	}

	// 입력 날짜에 해당하는 비트코인 환율을 DB에서 검색합니다.
	float rate = findRate(dateStr);
	if (rate < 0)
	{
		// 데이터베이스의 첫 날짜보다 더 이전의 날짜라면 환율 데이터가 없으므로 에러 처리합니다.
		std::cout << "Error: no exchange rate data for date " << dateStr << std::endl;
		return ;
	}

	// 정상적으로 모든 처리가 끝났다면 환율을 곱하여 결과를 출력합니다.
	std::cout << dateStr << " => " << value << " = " << value * rate << std::endl;
}

/**
 * @brief 날짜 문자열의 형식과 달력상의 유효성을 검사 (윤년 포함)
 * @details YYYY-MM-DD 형태인지, 숫자로 이루어져 있는지 확인 후 범위 검사를 수행합니다.
 * @param date "YYYY-MM-DD" 형식의 날짜 문자열
 * @return 달력에 존재하는 유효한 날짜이면 true, 그렇지 않으면 false 반환
 */
bool BitcoinExchange::validateDate(const std::string& date) const
{
	// YYYY-MM-DD 형식이므로 길이는 반드시 10이어야 하며, 4번과 7번 인덱스는 '-'여야 합니다.
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		return (false);
	}

	// '-' 문자를 제외한 나머지 자리가 모두 숫자인지 확인합니다.
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
		{
			continue ;
		}
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
		{
			return (false);
		}
	}

	// 연, 월, 일 문자열을 각각 잘라서 int로 변환합니다.
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	// 비트코인이 생긴 2009년 이전이거나 월, 일이 정상 범위를 벗어나면 false
	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		return (false);
	}

	// 4, 6, 9, 11월은 30일까지밖에 없습니다.
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			return (false);
		}
	}
	// 2월의 경우 윤년 계산이 필요합니다.
	else if (month == 2)
	{
		// 윤년 조건: 4로 나누어 떨어지고, 100으로 나누어 떨어지지 않거나, 400으로 나누어 떨어지는 해
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeap)
		{
			if (day > 29)
			{
				return (false);
			}
		}
		else
		{
			if (day > 28)
			{
				return (false);
			}
		}
	}
	return (true);
}

/**
 * @brief 주어진 날짜에 해당하는 비트코인 환율을 검색
 * @details 정확히 일치하는 날짜가 없으면 가장 가까운 과거 날짜의 환율을 반환합니다.
 * @param date 검색할 날짜 문자열
 * @return 찾은 환율값 (데이터베이스의 첫 날짜보다 과거일 경우 -1.0f 반환)
 */
float BitcoinExchange::findRate(const std::string& date) const
{
	// DB가 완전히 비어있는 경우 -1.0f를 반환 (비정상 케이스)
	if (_data.empty())
	{
		return (-1.0f);
	}

	// 1차적으로 맵에서 날짜가 정확히 일치하는지 찾습니다.
	std::map<std::string, float>::const_iterator it = _data.find(date);
	if (it != _data.end())
	{
		return (it->second);
	}

	// 일치하는 데이터가 없다면, std::map의 lower_bound를 사용하여
	// 파라미터 날짜보다 '크거나 같은' 첫 번째 원소의 반복자를 가져옵니다.
	it = _data.lower_bound(date);

	// 찾은 반복자가 map의 첫 번째 원소를 가리킨다면, 입력 날짜가 DB의 가장 과거 날짜보다도 이전임을 의미합니다.
	if (it == _data.begin())
	{
		return (-1.0f);
	}

	// 찾은 반복자를 한 칸 앞으로 되돌려서, 입력 날짜보다 '과거이면서 가장 가까운' 날짜를 가리키게 합니다.
	--it; // Decrement to get the closest past date
	return (it->second);
}

/**
 * @brief 문자열의 양 끝에 있는 공백(whitespace) 문자를 제거하는 헬퍼 함수
 * @param str 공백을 제거할 원본 문자열
 * @return 양 끝 공백이 제거된 새로운 문자열
 */
std::string BitcoinExchange::trim(const std::string& str) const
{
	// 공백으로 취급할 문자들의 집합 (스페이스, 탭, 줄바꿈 등)
	const std::string whitespace = " \t\n\r\f\v";

	// 앞에서부터 검색하여 처음으로 공백이 아닌 문자의 위치를 찾습니다.
	size_t first = str.find_first_not_of(whitespace);
	if (std::string::npos == first)
	{
		return (""); // 전부 공백 문자로만 이루어진 경우 빈 문자열 반환
	}

	// 뒤에서부터 검색하여 마지막으로 공백이 아닌 문자의 위치를 찾습니다.
	size_t last = str.find_last_not_of(whitespace);

	// 처음과 끝의 인덱스를 통해 유효한 문자열 부분만 잘라내어 반환합니다.
	return (str.substr(first, (last - first + 1)));
}

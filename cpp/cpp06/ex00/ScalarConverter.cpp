#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <cerrno>

// 사용자가 인스턴스를 생성하지 못하도록 의도적으로 비워두거나 막아둔 private 기본 메서드들
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// 문자열의 원래 타입을 식별하기 위한 열거형
enum e_type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

// 문자열 리터럴을 분석하여 어떤 타입(char, int, float, double)인지 감지하는 함수
static e_type detectType(const std::string& literal)
{
	// 추가 보완.
	// ./convert "" 를 넣어보면 알 수 있음.
	if (literal.empty())
	{
		return (INVALID);
	}

	// 1. 단일 문자(char) 판별: 길이가 1이고 숫자가 아닌 경우
	if (literal.length() == 1 && !std::isdigit(literal[0]))
	{
		return (CHAR);
	}

	char* endptr;
	// 2. 정수(int) 판별: std::strtol을 사용하여 끝까지 변환되었는지(endptr == '\0') 확인
	std::strtol(literal.c_str(), &endptr, 10);
	if (*endptr == '\0')
	{
		return (INT);
	}

	// 3. 실수(double/float) 판별: std::strtod 사용
	std::strtod(literal.c_str(), &endptr);
	if (*endptr == '\0')
	{
		return (DOUBLE); // 찌꺼기 문자 없이 끝났다면 double
	}
	if (*endptr == 'f' && *(endptr + 1) == '\0')
	{
		return (FLOAT); // 끝에 'f'가 하나만 붙어있으면 float
	}

	// 위 조건에 모두 해당하지 않으면 유효하지 않은 타입
	return (INVALID);
}

void ScalarConverter::convert(const std::string& literal) {
	// [단계 1] 특수 리터럴(pseudo-literal) 처리
	if (literal == "nan" || literal == "nanf" ||
		literal == "+inf" || literal == "+inff" ||
		literal == "-inf" || literal == "-inff" ||
		literal == "inf" || literal == "inff")
	{
		// 특수 리터럴은 char, int로 변환할 수 없으므로 즉시 impossible 출력
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";

		if (literal == "nan" || literal == "nanf")
		{
			std::cout << "float: nanf\n";
			std::cout << "double: nan\n";
		}
		else if (literal == "+inf" || literal == "+inff")
		{
			std::cout << "float: +inff\n";
			std::cout << "double: +inf\n";
		}
		else if (literal == "-inf" || literal == "-inff")
		{
			std::cout << "float: -inff\n";
			std::cout << "double: -inf\n";
		}
		else
		{
			std::cout << "float: inff\n";
			std::cout << "double: inf\n";
		}

		return ;
	}

	// [단계 2] 리터럴 타입 감지
	e_type type = detectType(literal);

	char c = 0;
	int i_val = 0;
	float f = 0.0f;
	double d = 0.0;
	bool isImpossible = false;

	if (type == CHAR)
	{
		// 감지된 타입이 char일 때: 기본값을 설정 후
		// 다른 타입들은 반드시 C++ 스타일 static_cast를 사용하여 형 변환
		c = literal[0];
		i_val = static_cast<int>(c);
		f = static_cast<float>(c);
		d = static_cast<double>(c);
	}
	else if (type == INT)
	{
		char* endptr;
		errno = 0;
		long l_val = std::strtol(literal.c_str(), &endptr, 10);

		// long 자체의 범위를 넘어버린 거 거대한 숫자인 경우 처리
		if (errno == ERANGE)
		{
			// std::numeric_limits를 사용해 int 범위 오버플로우 검증
			isImpossible = true; // 이 경우는 모든 타입 불가능(or 실수만 가능하게 정밀 제어)
		}
		else
		{
			i_val = static_cast<int>(l_val);
			c	  = static_cast<char>(l_val);
			f	  = static_cast<float>(l_val);
			d	  = static_cast<double>(l_val);
		}
	}
	else if (type == FLOAT)
	{
		char* endptr;
		errno = 0;
		double temp = std::strtod(literal.c_str(), &endptr);

		if (errno == ERANGE || temp < -std::numeric_limits<float>::max() || temp > std::numeric_limits<float>::max())
		{
			// float 범위 오버플로우 검증
			isImpossible = true;
		}
		else
		{
			f	  = static_cast<float>(temp);
			c	  = static_cast<char>(f);
			i_val = static_cast<int>(f);
			d	  = static_cast<double>(f);
		}
	}
	else if (type == DOUBLE)
	{
		char* endptr;
		errno = 0;
		d = std::strtod(literal.c_str(), &endptr);

		if (errno == ERANGE)
		{
			isImpossible = true;
		}
		else
		{
			c	  = static_cast<char>(d);
			i_val = static_cast<int>(d);
			f	  = static_cast<float>(d);
		}
	}
	else if (type == INVALID)
	{
		isImpossible = true;
	}

	// [단계 3] 스칼라 타입 결과 출력

	std::cout << "char: ";
	if (isImpossible)
	{
		std::cout << "impossible\n";
	}
	else
	{
		// char 오버플로우 체크를 위해 변환 전 타입 기반 double 값을 참조값으로 사용
		double ref;
		if (type == DOUBLE)
		{
			ref = d;
		}
		else if (type == FLOAT)
		{
			ref = static_cast<double>(f);
		}
		else if (type == INT)
		{
			ref = static_cast<double>(i_val);
		}
		else
		{ // type == CHAR 인 경우
			ref = static_cast<double>(c);
		}

		if (ref < std::numeric_limits<char>::min() || ref > std::numeric_limits<char>::max())
		{
			std::cout << "impossible\n";
		}
		else if (!std::isprint(static_cast<unsigned char>(c)))
		{
			// 출력 불가능한 제어 문자 확인
			std::cout << "Non displayable\n";
		}
		else
		{
			std::cout << "'" << c << "'\n";
		}
	}

	std::cout << "int: ";
	if (isImpossible)
	{
		std::cout << "impossible\n";
	}
	else
	{
		// int 오버플로우 체크를 위해 원본 데이터 타입에 맞는 값을 double ref에 저장
		double ref;
		if (type == DOUBLE)
		{
			ref = d;
		}
		else if (type == FLOAT)
		{
			ref = static_cast<double>(f);
		}
		else if (type == INT)
		{
			ref = d;
		}
		else
		{ // type == CHAR 인 경우
			ref = static_cast<double>(c);
		}

		if (ref < std::numeric_limits<int>::min() || ref > std::numeric_limits<int>::max())
		{
			std::cout << "impossible\n";
		}
		else
		{
			std::cout << i_val << "\n";
		}
	}

	// 소수점 아래 값이 없는 경우 .0f 유지를 위한 포맷 처리 (C++98 스타일)
	std::cout << "float: ";
	if (isImpossible)
	{
		std::cout << "impossible\n";
	}
	else if (f == std::floor(f) && !std::isinf(f))
	{
		std::cout << std::fixed << std::setprecision(1) << f << "f\n";
	}
	else
	{
		std::cout << f << "f\n";
	}

	// 다음 출력을 위해 앞서 float 출력 시 설정한 std::fixed 포맷 해제
	std::cout.unsetf(std::ios_base::floatfield);
	std::cout << "double: ";
	if (isImpossible)
	{
		std::cout << "impossible\n";
	}
	else if (d == std::floor(d) && !std::isinf(d))
	{
		std::cout << std::fixed << std::setprecision(1) << d << "\n";
	}
	else
	{
		std::cout << d << "\n";
	}
}
#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <cerrno>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

enum e_type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

// [기존 유지] 문자열 리터럴의 원본 타입을 분석하는 함수
static e_type detectType(const std::string& literal)
{
	if (literal.empty())
	{
		return (INVALID);
	}
	if (literal.length() == 1 && !std::isdigit(literal[0]))
	{
		return (CHAR);
	}

	char* endptr;
	std::strtol(literal.c_str(), &endptr, 10);
	if (*endptr == '\0')
	{
		return (INT);
	}

	std::strtod(literal.c_str(), &endptr);
	if (*endptr == '\0')
	{
		return (DOUBLE);
	}
	if (*endptr == 'f' && *(endptr + 1) == '\0')
	{
		return (FLOAT);
	}

	return (INVALID);
}

// =========================================================================
// 🛠️ 새로 분리된 내부 도우미(Helper) 함수들 (요청하신 {} 스타일 적용)
// =========================================================================

// 도우미 1: 특수 리터럴(nan, inf) 감지 및 즉시 출력 전담
static bool handlePseudoLiteral(const std::string& literal)
{
	if (literal != "nan" && literal != "nanf" &&
		literal != "+inf" && literal != "+inff" &&
		literal != "-inf" && literal != "-inff" &&
		literal != "inf" && literal != "inff")
	{
		return (false);
	}

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
	return (true);
}

// 도우미 2: 정수/문자 오버플로우 검증을 위해 원본 대조군 값을 안전하게 double로 획득
static double getOriginalValueAsDouble(e_type type, char c, int i_val, float f, double d)
{
	if (type == DOUBLE)
	{
		return (d);
	}
	if (type == FLOAT)
	{
		return (static_cast<double>(f));
	}
	if (type == INT)
	{
		return (d);
	}
	return (static_cast<double>(c));
}

// 도우미 3: char 타입 최종 출력 제어
static void printChar(bool isImpossible, double ref, char c)
{
	std::cout << "char: ";
	if (isImpossible || ref < std::numeric_limits<char>::min() || ref > std::numeric_limits<char>::max())
	{
		std::cout << "impossible\n";
	}
	else if (!std::isprint(static_cast<unsigned char>(c)))
	{
		std::cout << "Non displayable\n";
	}
	else
	{
		std::cout << "'" << c << "'\n";
	}
}

// 도우미 4: int 타입 최종 출력 제어
static void printInt(bool isImpossible, double ref, int i_val)
{
	std::cout << "int: ";
	if (isImpossible || ref < std::numeric_limits<int>::min() || ref > std::numeric_limits<int>::max())
	{
		std::cout << "impossible\n";
	}
	else
	{
		std::cout << i_val << "\n";
	}
}

// 도우미 5: float 타입 최종 출력 제어
static void printFloat(bool isImpossible, float f)
{
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
	std::cout.unsetf(std::ios_base::floatfield);
}

// 도우미 6: double 타입 최종 출력 제어
static void printDouble(bool isImpossible, double d)
{
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

// =========================================================================
// 🚀 메인 엔트리
// =========================================================================

void ScalarConverter::convert(const std::string& literal)
{
	// [단계 1] 특수 리터럴 처리 및 가드 체일
	if (handlePseudoLiteral(literal))
	{
		return;
	}

	// [단계 2] 리터럴 타입 감지 및 실제 변수 파싱
	e_type type = detectType(literal);

	char c = 0;
	int i_val = 0;
	float f = 0.0f;
	double d = 0.0;
	bool isImpossible = false;

	if (type == CHAR)
	{
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

		if (errno == ERANGE)
		{
			isImpossible = true;
		}
		else
		{
			i_val = static_cast<int>(l_val);
			c     = static_cast<char>(l_val);
			f     = static_cast<float>(l_val);
			d     = static_cast<double>(l_val);
		}
	}
	else if (type == FLOAT)
	{
		char* endptr;
		errno = 0;
		double temp = std::strtod(literal.c_str(), &endptr);

		if (errno == ERANGE || temp < -std::numeric_limits<float>::max() || temp > std::numeric_limits<float>::max())
		{
			isImpossible = true;
		}
		else
		{
			f     = static_cast<float>(temp);
			c     = static_cast<char>(f);
			i_val = static_cast<int>(f);
			d     = static_cast<double>(f);
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
			c     = static_cast<char>(d);
			i_val = static_cast<int>(d);
			f     = static_cast<float>(d);
		}
	}
	else if (type == INVALID)
	{
		isImpossible = true;
	}

	// [단계 3] 스칼라 타입 결과 출력
	double ref = getOriginalValueAsDouble(type, c, i_val, f, d);

	printChar(isImpossible, ref, c);
	printInt(isImpossible, ref, i_val);
	printFloat(isImpossible, f);
	printDouble(isImpossible, d);
}
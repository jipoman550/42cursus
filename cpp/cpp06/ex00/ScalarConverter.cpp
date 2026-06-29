#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <cerrno>

// OCF(Orthodox Canonical Form) 요구 사항을 만족하기 위한 기본 생성자, 복사 생성자, 대입 연산자, 소멸자
// 인스턴스화를 방지하기 위해 모두 private으로 선언되어 있으므로 비워둡니다 (hpp 파일 참고).
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// 리터럴의 원본 타입을 구분하기 위한 열거형
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
	// 1. 빈 문자열인 경우 유효하지 않음
	if (literal.empty())
	{
		return (INVALID);
	}
	// 2. 길이가 1이고 숫자가 아닌 경우 단일 문자(char) 타입으로 간주
	if (literal.length() == 1 && !std::isdigit(literal[0]))
	{
		return (CHAR);
	}

	char* endptr;
	// 3. 10진수 정수로 변환 시도
	std::strtol(literal.c_str(), &endptr, 10);
	// 문자열 끝까지 모두 변환되었으면 int 타입
	if (*endptr == '\0')
	{
		return (INT);
	}

	// 4. double로 변환 시도
	std::strtod(literal.c_str(), &endptr);
	// 문자열 끝까지 모두 변환되었으면 double 타입
	if (*endptr == '\0')
	{
		return (DOUBLE);
	}
	// 'f'로 끝나고 그 뒤에 아무것도 없으면 float 타입 (예: 4.2f)
	if (*endptr == 'f' && *(endptr + 1) == '\0')
	{
		return (FLOAT);
	}

	// 그 외의 경우 유효하지 않은 타입
	return (INVALID);
}

// =========================================================================
// 🛠️ 새로 분리된 내부 도우미(Helper) 함수들 (요청하신 {} 스타일 적용)
// =========================================================================

// 도우미 1: 특수 리터럴(nan, inf) 감지 및 즉시 출력 전담
static bool handlePseudoLiteral(const std::string& literal)
{
	// 정의된 특수 리터럴이 아닌 경우 false 반환하여 일반 변환 로직으로 넘김
	if (literal != "nan" && literal != "nanf" &&
		literal != "+inf" && literal != "+inff" &&
		literal != "-inf" && literal != "-inff" &&
		literal != "inf" && literal != "inff")
	{
		return (false);
	}

	// 특수 리터럴인 경우 char와 int는 변환이 불가능하므로 impossible 출력
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";

	// 각각의 특수 리터럴에 맞추어 float 및 double 결과 출력
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
static double getOriginalValueAsDouble(e_type type, char c, float f, double d)
{
	// 감지된 원본 타입에 맞추어 값을 double 타입으로 일원화하여 반환
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
	// 아예 변환 불가능한 값이거나 char의 표현 범위를 벗어난 경우
	if (isImpossible || ref < std::numeric_limits<char>::min() || ref > std::numeric_limits<char>::max())
	{
		std::cout << "impossible\n";
	}
	// 출력 불가능한 문자(Non-printable character)인 경우
	else if (!std::isprint(static_cast<unsigned char>(c)))
	{
		std::cout << "Non displayable\n";
	}
	// 정상 출력 가능한 문자
	else
	{
		std::cout << "'" << c << "'\n";
	}
}

// 도우미 4: int 타입 최종 출력 제어
static void printInt(bool isImpossible, double ref, int i_val)
{
	std::cout << "int: ";
	// 아예 변환 불가능한 값이거나 int의 표현 범위를 벗어난 경우
	if (isImpossible || ref < std::numeric_limits<int>::min() || ref > std::numeric_limits<int>::max())
	{
		std::cout << "impossible\n";
	}
	// 정상 출력
	else
	{
		std::cout << i_val << "\n";
	}
}

// 도우미 5: float 타입 최종 출력 제어
static void printFloat(bool isImpossible, float f)
{
	std::cout << "float: ";
	// 변환 불가능한 값이면 impossible 출력
	if (isImpossible)
	{
		std::cout << "impossible\n";
	}
	// 정수처럼 소수점 이하가 없지만 무한대가 아닌 경우 강제로 소수점 1자리(.0)까지 출력
	else if (f == std::floor(f) && !std::isinf(f))
	{
		std::cout << std::fixed << std::setprecision(1) << f << "f\n";
	}
	// 일반적인 소수점이 있는 형태
	else
	{
		std::cout << f << "f\n";
	}
	// 다음 출력을 위해 부동 소수점 형식(fixed) 해제
	std::cout.unsetf(std::ios_base::floatfield);
}

// 도우미 6: double 타입 최종 출력 제어
static void printDouble(bool isImpossible, double d)
{
	std::cout << "double: ";
	// 변환 불가능한 값이면 impossible 출력
	if (isImpossible)
	{
		std::cout << "impossible\n";
	}
	// 정수처럼 소수점 이하가 없지만 무한대가 아닌 경우 강제로 소수점 1자리(.0)까지 출력
	else if (d == std::floor(d) && !std::isinf(d))
	{
		std::cout << std::fixed << std::setprecision(1) << d << "\n";
	}
	// 일반적인 소수점이 있는 형태
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
	// [단계 1] 특수 리터럴 처리 및 가드 체크 (특수 리터럴이면 바로 종료)
	if (handlePseudoLiteral(literal))
	{
		return ;
	}

	// [단계 2] 리터럴 타입 감지 및 실제 변수 파싱
	e_type type = detectType(literal);

	char c				= 0;
	int i_val			= 0;
	float f				= 0.0f;
	double d			= 0.0;
	bool isImpossible	= false; // 변환 중 오버플로우나 오류 발생 여부를 저장하는 플래그

	// [단계 2-1] 파악된 타입별로 파싱 진행하고 다른 3가지 타입으로 명시적 형변환(static_cast) 수행
	if (type == CHAR)
	{
		c		= literal[0];
		i_val	= static_cast<int>(c);
		f		= static_cast<float>(c);
		d		= static_cast<double>(c);
	}
	else if (type == INT)
	{
		char* endptr;
		errno = 0;
		long l_val = std::strtol(literal.c_str(), &endptr, 10);

		// strtol은 long을 반환하므로 오버플로우가 나면 ERANGE가 설정됨
		if (errno == ERANGE)
		{
			isImpossible = true;
		}
		else
		{
			i_val	= static_cast<int>(l_val);
			c		= static_cast<char>(l_val);
			f		= static_cast<float>(l_val);
			d		= static_cast<double>(l_val);
		}
	}
	else if (type == FLOAT)
	{
		char* endptr;
		errno = 0;
		double temp = std::strtod(literal.c_str(), &endptr);

		// strtod 파싱 과정에서 에러가 났거나 float 표현 범위를 넘어서는 경우
		if (errno == ERANGE || temp < -std::numeric_limits<float>::max() || temp > std::numeric_limits<float>::max())
		{
			isImpossible = true;
		}
		else
		{
			f		= static_cast<float>(temp);
			c		= static_cast<char>(f);
			i_val	= static_cast<int>(f);
			d		= static_cast<double>(f);
		}
	}
	else if (type == DOUBLE)
	{
		char* endptr;
		errno = 0;
		d = std::strtod(literal.c_str(), &endptr);

		// strtod 파싱 과정에서 오버플로우가 났는지 검사
		if (errno == ERANGE)
		{
			isImpossible = true;
		}
		else
		{
			c		= static_cast<char>(d);
			i_val	= static_cast<int>(d);
			f		= static_cast<float>(d);
		}
	}
	else if (type == INVALID)
	{
		// 그 어떤 타입으로도 변환할 수 없는 유효하지 않은 문자열
		isImpossible = true;
	}

	// [단계 3] 스칼라 타입 결과 출력
	// 모든 값이 오버플로우되었는지(impossible) 확인하기 위한 기준점(ref) 획득
	double ref = getOriginalValueAsDouble(type, c, f, d);

	// 각 스칼라 타입 결과 출력 함수 호출
	printChar(isImpossible, ref, c);
	printInt(isImpossible, ref, i_val);
	printFloat(isImpossible, f);
	printDouble(isImpossible, d);
}

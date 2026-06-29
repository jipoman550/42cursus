#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
private:
	// 인스턴스화를 방지하기 위해 OCF(Orthodox Canonical Form)를 모두 private으로 선언합니다.
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

public:
	// 문자열 리터럴을 인자로 받아 변환을 수행하는 유일한 public static 메서드입니다.
	static void convert(const std::string& literal);
};

#endif
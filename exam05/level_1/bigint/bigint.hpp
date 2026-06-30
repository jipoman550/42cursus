#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
public:
	// 생성자 및 소멸자
	bigint(unsigned long long value = 0);
	bigint(const std::string& s);
	bigint(const bigint& other);
	~bigint();

	// 대입 연산자
	bigint& operator=(const bigint& other);

	// 비교 연산자
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	bool operator==(const bigint& other) const;
	bool operator!=(const bigint& other) const;

	// 산술 연산자
	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);
	bigint& operator++();       // 전위 증가
	bigint operator++(int);    // 후위 증가

	// 디지털 시프트 연산자 (int)
	bigint operator<<(int n) const;
	bigint& operator<<=(int n);
	bigint operator>>(int n) const;
	bigint& operator>>=(int n);

	// 디지털 시프트 연산자 (bigint)
	bigint operator<<(const bigint& n) const;
	bigint& operator<<=(const bigint& n);
	bigint operator>>(const bigint& n) const;
	bigint& operator>>=(const bigint& n);

	// 출력 연산자
	friend std::ostream& operator<<(std::ostream& os, const bigint& bi);

private:
	std::string value_; // 숫자를 문자열로 저장

	void trim(); // 불필요한 앞쪽의 '0'을 제거하는 헬퍼 함수
	int to_int() const; // 시프트 연산을 위해 bigint를 int로 변환하는 헬퍼 함수
};

#endif // BIGINT_HPP
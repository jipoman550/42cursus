#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
public:
	// =================================================================
	// 1. 생성자 및 소멸자 (Constructors & Destructor)
	// =================================================================
	// Tip: 다양한 타입(숫자, 문자열, 다른 bigint)으로 객체를 생성할 수 있도록 지원합니다.
	bigint(unsigned long long value = 0);
	bigint(const std::string& s);
	bigint(const bigint& other);
	~bigint();

	// =================================================================
	// 2. 대입 연산자 (Assignment Operator)
	// =================================================================
	bigint& operator=(const bigint& other);

	// =================================================================
	// 3. 비교 연산자 (Comparison Operators)
	// =================================================================
	// Tip: 6개의 연산자 중 '<'와 '=='만 제대로 구현하고 나머지는 이를 재활용하는 것이 핵심입니다.
	// Tip: const 멤버 함수로 선언해야 const bigint 객체에 대해서도 비교가 가능합니다. (e.g. const bigint a(42);)
	bool operator<(const bigint& other) const;
	bool operator==(const bigint& other) const;
	// Tip: 아래 4개 연산자는 위 2개를 조합하여 만듭니다. 시험장에서 구현 시간을 대폭 단축할 수 있습니다.
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	bool operator!=(const bigint& other) const;

	// =================================================================
	// 4. 산술 연산자 (Arithmetic Operators)
	// =================================================================
	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);
	// Tip: 전위(++a)와 후위(a++)는 반환 타입과 시그니처가 다릅니다.
	bigint& operator++();       // 전위 증가 (Pre-increment)
	bigint operator++(int);    // 후위 증가 (Post-increment)

	// =================================================================
	// 5. 디지털 시프트 연산자 (Digit Shift Operators)
	// =================================================================
	// Tip: int를 받는 버전이 실제 로직을 수행합니다.
	bigint operator<<(int n) const;
	bigint& operator<<=(int n);
	bigint operator>>(int n) const;
	bigint& operator>>=(int n);

	// Tip: bigint를 받는 버전은 to_int()를 통해 int 버전으로 작업을 전달(forwarding)하기만 합니다.
	bigint operator<<(const bigint& n) const;
	bigint& operator<<=(const bigint& n);
	bigint operator>>(const bigint& n) const;
	bigint& operator>>=(const bigint& n);

	// =================================================================
	// 6. 출력 스트림 연산자 (Output Stream Operator)
	// =================================================================
	// Tip: 멤버 함수가 아닌 일반 함수로 선언하고, private 멤버인 value_에 접근하기 위해 'friend'로 선언합니다.
	friend std::ostream& operator<<(std::ostream& os, const bigint& bi);

private:
	std::string value_; // 숫자를 문자열로 저장

	// =================================================================
	// 7. 헬퍼 함수 (Helper Functions)
	// =================================================================
	void trim();        // "007" -> "7", "00" -> "0" 처럼 불필요한 앞쪽 '0'을 제거합니다.
	int to_int() const; // 시프트 연산을 위해 bigint를 int로 변환합니다.
};

#endif // BIGINT_HPP
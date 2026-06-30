#include "bigint.hpp"
#include <algorithm>
#include <stdexcept>
#include <sstream> // for std::stringstream
#include <cstdlib> // for std::atoi

// private: 불필요한 앞쪽의 '0'을 제거합니다. (예: "007" -> "7", "000" -> "0")
void bigint::trim() {
	if (value_.length() > 1) {
		size_t first_digit = value_.find_first_not_of('0');
		if (std::string::npos != first_digit) {
			value_ = value_.substr(first_digit);
		} else {
			// 모든 문자가 '0'인 경우
			value_ = "0";
		}
	}
}

// private: 시프트 연산자에서 사용할 bigint 값을 int로 변환합니다.
int bigint::to_int() const {
	// 과제에서는 시프트 양이 int 범위를 넘지 않는다고 가정합니다.
	// atoi는 변환 실패 시 0을 반환하며, C++98 표준입니다.
	return std::atoi(value_.c_str());
}

// 생성자
bigint::bigint(unsigned long long value) {
	std::stringstream ss;
	ss << value;
	value_ = ss.str();
}

bigint::bigint(const std::string& s) : value_(s) {
	// 입력 문자열이 비어있거나 숫자가 아닌 문자를 포함하면 "0"으로 초기화합니다.
	if (value_.empty() || value_.find_first_not_of("0123456789") != std::string::npos) {
		value_ = "0";
	} else {
		trim(); // "007" 같은 입력을 "7"로 정리합니다.
	}
}

bigint::bigint(const bigint& other) : value_(other.value_) {}

// 소멸자
bigint::~bigint() {}

// 대입 연산자
bigint& bigint::operator=(const bigint& other) {
	if (this != &other) {
		value_ = other.value_;
	}
	return *this;
}

// 비교 연산자
bool bigint::operator<(const bigint& other) const {
	if (value_.length() != other.value_.length()) {
		return value_.length() < other.value_.length();
	}
	return value_ < other.value_;
}

bool bigint::operator>(const bigint& other) const {
	return other < *this;
}

bool bigint::operator<=(const bigint& other) const {
	return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const {
	return !(*this < other);
}

bool bigint::operator==(const bigint& other) const {
	return value_ == other.value_;
}

bool bigint::operator!=(const bigint& other) const {
	return !(*this == other);
}

// 산술 연산자
bigint bigint::operator+(const bigint& other) const {
	std::string s1 = value_;
	std::string s2 = other.value_;
	std::string result = "";
	int carry = 0;

	int i = s1.length() - 1;
	int j = s2.length() - 1;

	// 초등학교 산수처럼 끝자리부터 더해나갑니다.
	while (i >= 0 || j >= 0 || carry) {
		int sum = carry;
		if (i >= 0) {
			sum += s1[i--] - '0';
		}
		if (j >= 0) {
			sum += s2[j--] - '0';
		}
		result += (sum % 10) + '0';
		carry = sum / 10;
	}

	std::reverse(result.begin(), result.end()); // 결과 문자열을 뒤집어 올바른 순서로 만듭니다.
	return bigint(result);
}

bigint& bigint::operator+=(const bigint& other) {
	*this = *this + other;
	return *this;
}

bigint& bigint::operator++() { // 전위
	*this += 1;
	return *this;
}

bigint bigint::operator++(int) { // 후위
	bigint temp = *this;
	++(*this);
	return temp;
}

// 디지털 시프트 연산자 (int)
bigint bigint::operator<<(int n) const {
	if (value_ == "0" || n <= 0) {
		return *this;
	}
	return bigint(value_ + std::string(n, '0'));
}

bigint& bigint::operator<<=(int n) {
	if (value_ != "0" && n > 0) {
		value_ += std::string(n, '0');
	}
	return *this;
}

bigint bigint::operator>>(int n) const {
	if (n <= 0) {
		return *this;
	}
	if (static_cast<size_t>(n) >= value_.length()) {
		return bigint(0);
	}
	return bigint(value_.substr(0, value_.length() - n));
}

bigint& bigint::operator>>=(int n) {
	if (n > 0) {
		if (static_cast<size_t>(n) >= value_.length()) {
			value_ = "0";
		} else {
			value_ = value_.substr(0, value_.length() - n);
		}
	}
	return *this;
}

// 디지털 시프트 연산자 (bigint)
bigint bigint::operator<<(const bigint& n) const { return *this << n.to_int(); }
bigint& bigint::operator<<=(const bigint& n) { return *this <<= n.to_int(); }
bigint bigint::operator>>(const bigint& n) const { return *this >> n.to_int(); }
bigint& bigint::operator>>=(const bigint& n) { return *this >>= n.to_int(); }

// 출력 연산자
std::ostream& operator<<(std::ostream& os, const bigint& bi) {
	os << bi.value_;
	return os;
}
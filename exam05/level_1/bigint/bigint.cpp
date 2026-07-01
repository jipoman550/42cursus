#include "bigint.hpp"
#include <algorithm>
#include <stdexcept>
#include <sstream> // for std::stringstream
#include <cstdlib> // for std::atoi

// [시험장 Tip] 서브젝트의 "leading zeros" 금지 조항을 충족시키는 핵심 헬퍼 함수입니다.
// 생성자나 연산 결과 끝에 항상 호출하여 "007" -> "7", "0" -> "0"을 보장해야 합니다.
// 문자열 전체가 '0'일 때 (e.g., "000") "0" 하나만 남기는 엣지 케이스를 주의하세요.
void bigint::trim()
{
	// 길이가 1보다 클 때만 처리. "0"은 건드리지 않습니다.
	if (value_.length() > 1)
	{
		size_t first_digit = value_.find_first_not_of('0');
		if (std::string::npos != first_digit)
		{
			value_ = value_.substr(first_digit);
		}
		else
		{
			// 모든 문자가 '0'인 경우
			value_ = "0";
		}
	}
}

// [시험장 Tip] bigint를 받는 시프트 연산자를 int를 받는 버전으로 포워딩하기 위한 헬퍼입니다.
// 시험 환경에서는 시프트 값이 int 범위를 넘지 않는다고 가정할 수 있으므로 atoi로 충분합니다.
// atoi는 C-style 문자열(const char*)을 인자로 받으므로 .c_str()를 사용해야 합니다.
int bigint::to_int() const {
	return std::atoi(value_.c_str());
}

// [시험장 Tip] unsigned long long 같은 큰 숫자 타입을 문자열로 변환할 때 가장 안전하고 쉬운 방법입니다.
// 이 패턴을 기억해두면 구현이 매우 간단해집니다.
bigint::bigint(unsigned long long value) {
	std::stringstream ss;
	ss << value;
	value_ = ss.str();
}

// [시험장 Tip] 문자열로 생성할 때는 방어 코드가 중요합니다.
// 1. 빈 문자열인가?
// 2. 숫자가 아닌 문자가 포함되었는가? (`find_first_not_of` 활용)
// 위 두 경우 "0"으로 초기화합니다. 유효한 입력이라도 "00123" 형태일 수 있으므로 `trim()`을 호출해 정규화합니다.
bigint::bigint(const std::string& s) : value_(s) {
	// 입력 문자열이 비어있거나 숫자가 아닌 문자를 포함하면 "0"으로 초기화합니다.
	if (value_.empty() || value_.find_first_not_of("0123456789") != std::string::npos) {
		value_ = "0";
	} else {
		trim(); // "007" 같은 입력을 "7"로 정리합니다.
	}
}

// [시험장 Tip] 복사 생성자는 컴파일러가 기본으로 만들어주지만, 명시적으로 작성하는 습관을 들이는 것이 좋습니다.
// 여기서는 단순히 내부 문자열 `value_`를 복사하면 됩니다.
bigint::bigint(const bigint& other) : value_(other.value_) {}

// [시험장 Tip] `std::string`이 내부에서 동적 할당을 관리해주므로, 소멸자에서 직접 해제할 메모리는 없습니다.
bigint::~bigint() {}

// [시험장 Tip] `a = a;`와 같은 자기 대입을 방지하기 위해 `if (this != &other)` 가드를 추가하는 것이 표준적인 구현입니다.
// 이를 통해 불필요한 작업을 막고 안정성을 높입니다.
// 대입 연산자
bigint& bigint::operator=(const bigint& other) {
	if (this != &other) {
		value_ = other.value_;
	}
	return *this;
}

// [시험장 Tip] 비교 연산의 핵심입니다. 두 단계로 비교합니다.
// 1. 문자열의 길이를 먼저 비교합니다. 길이가 짧으면 더 작은 수입니다. (e.g., "99" < "100")
// 2. 길이가 같다면, 문자열을 사전 순서로 비교합니다. (e.g., "123" < "124")
bool bigint::operator<(const bigint& other) const {
	if (value_.length() != other.value_.length()) {
		return value_.length() < other.value_.length();
	}
	return value_ < other.value_;
}

// [시험장 Tip] 두 번째 핵심 비교 연산자입니다. 내부 문자열 `value_`가 같은지만 확인하면 됩니다.
bool bigint::operator==(const bigint& other) const {
	return value_ == other.value_;
}

// [시험장 Tip] 아래 4개의 연산자는 '<'와 '=='를 재활용하여 구현합니다.
// 이 패턴은 시험장에서 코드를 외우는 부담을 줄여주고 실수를 방지하는 최고의 전략입니다.
// a > b  는 b < a 와 동일합니다.
bool bigint::operator>(const bigint& other) const {
	return other < *this;
}

// a <= b 는 a > b 가 아닌 것과 동일합니다.
bool bigint::operator<=(const bigint& other) const {
	return !(*this > other); // !(other < *this) 와 같습니다.
}

// a >= b 는 a < b 가 아닌 것과 동일합니다.
bool bigint::operator>=(const bigint& other) const {
	return !(*this < other);
}

// a != b 는 a == b 가 아닌 것과 동일합니다.
bool bigint::operator!=(const bigint& other) const {
	return !(*this == other);
}

// [시험장 Tip] 초등학교 때 배운 세로셈 덧셈을 코드로 옮긴다고 생각하세요.
// 1. 두 문자열의 끝(일의 자리)에서부터 시작합니다.
// 2. `carry`(올림수)를 관리합니다.
// 3. 각 자리의 합(`sum`)을 구하고, 결과 문자열에는 `sum % 10`을 추가하고, `carry`는 `sum / 10`으로 업데이트합니다.
// 4. 결과가 뒤집힌 순서로 만들어지므로(일의 자리부터 추가되므로), 마지막에 `std::reverse`를 꼭 호출해야 합니다.
bigint bigint::operator+(const bigint& other) const {
	std::string s1 = value_;
	std::string s2 = other.value_;
	std::string result = "";
	int carry = 0;

	int i = s1.length() - 1;
	int j = s2.length() - 1;

	// 끝자리부터 더해나갑니다.
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

// [시험장 Tip] `operator+`를 이미 구현했다면 `*this = *this + other;` 한 줄로 간단하게 구현할 수 있습니다.
// 코드 재사용의 좋은 예입니다.
bigint& bigint::operator+=(const bigint& other) {
	*this = *this + other;
	return *this;
}

// [시험장 Tip] 전위 증가(++a): 객체를 먼저 1 증가시키고, '증가된 후의 자기 자신'을 반환합니다.
// 반환 타입이 `bigint&`인 것에 주의하세요. 자기 자신의 참조를 반환하여 `++(++a)` 같은 연쇄적인 사용이 가능하게 합니다.
// `*this += 1;`로 구현하고 `return *this;`를 합니다.
bigint& bigint::operator++() { // 전위
	*this += 1;
	return *this;
}

// [시험장 Tip] 후위 증가(a++): '증가하기 전의 값'을 먼저 반환하고, 그 뒤에 객체를 1 증가시킵니다.
// 1. 매개변수로 `int`를 받는 것이 전위 연산자와의 문법적 차이점입니다. 이 `int`는 사용되지 않습니다.
// 2. 구현 3단계: (1) 현재 상태를 복사, (2) 자기 자신을 증가, (3) 복사본을 반환.
// 3. 반환 타입은 값(`bigint`)입니다. 참조가 아닙니다.
bigint bigint::operator++(int) { // 후위
	bigint temp = *this;
	++(*this);
	return temp;
}

// [시험장 Tip] Digit Shift는 10진수 기준 자릿수 이동입니다. `42 << 3`은 `42000`이 됩니다.
// 구현은 간단합니다. 숫자 문자열 뒤에 '0'을 `n`개 붙이면 됩니다. `std::string(n, '0')` 구문을 기억하세요.
// `value_`가 "0"이거나 `n`이 0 이하이면 아무 작업도 하지 않는 엣지 케이스를 처리해야 합니다.
bigint bigint::operator<<(int n) const {
	// n이 음수이거나, 현재 값이 0이면 아무 변화가 없으므로 자기 자신을 복사하여 반환합니다.
	if (value_ == "0" || n <= 0) {
		return *this;
	}
	// 기존 문자열 뒤에 '0'을 n개 붙인 새 문자열로 bigint를 생성하여 반환합니다.
	return bigint(value_ + std::string(n, '0'));
}

bigint& bigint::operator<<=(int n) {
	if (value_ != "0" && n > 0) {
		value_ += std::string(n, '0');
	}
	return *this;
}

// [시험장 Tip] `1337 >> 2`는 `13`이 됩니다. 문자열 끝에서 `n`개의 문자를 제거하는 것과 같습니다.
// `substr(0, value_.length() - n)`을 사용하면 쉽게 구현할 수 있습니다.
// `n`이 문자열 길이보다 크거나 같으면 결과는 "0"이 되어야 합니다. 이 엣지 케이스를 반드시 처리해야 합니다.
bigint bigint::operator>>(int n) const {
	if (n <= 0) {
		return *this;
	}
	// 시프트할 길이가 현재 숫자 길이보다 크거나 같으면 결과는 0입니다.
	if (static_cast<size_t>(n) >= value_.length()) {
		return bigint(0);
	}
	// 앞에서부터 (길이 - n) 만큼의 부분 문자열을 취합니다.
	return bigint(value_.substr(0, value_.length() - n));
}

bigint& bigint::operator>>=(int n) {
	if (n > 0) {
		// 시프트할 길이가 현재 숫자 길이보다 크거나 같으면 "0"이 됩니다.
		if (static_cast<size_t>(n) >= value_.length()) {
			value_ = "0";
		} else {
			value_ = value_.substr(0, value_.length() - n);
		}
	}
	return *this;
}

// [시험장 Tip] `bigint`를 받는 시프트 연산자는 코드를 중복해서 작성할 필요가 없습니다.
// `to_int()` 헬퍼 함수를 호출하여 `int`를 받는 버전을 재사용하면 됩니다.
// 이는 시험장에서 구현을 단순화하는 핵심 전략입니다.
bigint bigint::operator<<(const bigint& n) const { return *this << n.to_int(); }
bigint& bigint::operator<<=(const bigint& n) { return *this <<= n.to_int(); }
bigint bigint::operator>>(const bigint& n) const { return *this >> n.to_int(); }
bigint& bigint::operator>>=(const bigint& n) { return *this >>= n.to_int(); }

// [시험장 Tip] `std::cout << a;`를 가능하게 합니다.
// private 멤버인 `value_`에 접근해야 하므로 헤더에서 `friend`로 선언되었습니다.
std::ostream& operator<<(std::ostream& os, const bigint& bi) {
	os << bi.value_;
	return os;
}
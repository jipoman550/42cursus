#include "bigint.hpp"
#include <sstream>
#include <algorithm>
#include <cstdlib>

void bigint::trim()
{
	if (value_.length() > 1)
	{
		size_t first_digit = value_.find_first_not_of('0');
		if (std::string::npos != first_digit)
		{
			value_ = value_.substr(first_digit);
		}
		else
		{
			value_ = "0";
		}
	}
}

int bigint::to_int() const
{
	return (std::atoi(value_.c_str()));
}

// =======================

bigint::bigint(unsigned long long value)
{
	std::stringstream ss;
	ss << value;
	value_ = ss.str();
}

bigint::bigint(const std::string& s) : value_(s)
{
	if (value_.empty() || value_.find_first_not_of("0123456789") != std::string::npos)
	{
		value_ = "0";
	}
	else
	{
		trim();
	}
}

bigint::bigint(const bigint& other) : value_(other.value_) {}

bigint::~bigint() {}

// ==========================

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
	{
		value_ = other.value_;
	}
	return (*this);
}

// ============================

bool bigint::operator<(const bigint& other) const
{
	if (value_.length() != other.value_.length())
	{
		return (value_.length() < other.value_.length());
	}
	return (value_ < other.value_);
}

bool bigint::operator==(const bigint& other) const
{
	return (value_ == other.value_);
}

bool bigint::operator>(const bigint& other) const { return (other < *this); }
bool bigint::operator<=(const bigint& other) const { return !(*this > other); }
bool bigint::operator>=(const bigint& other) const { return !(*this < other); }
bool bigint::operator!=(const bigint& other) const { return !(*this == other); }

// ============================

bigint bigint::operator+(const bigint& other) const
{
	std::string s1 = value_;
	std::string s2 = other.value_;
	std::string result = "";
	int carry = 0;

	int i = s1.length() - 1;
	int j = s2.length() - 1;

	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;
		if (i >= 0)
		{
			sum += s1[i--] - '0';
		}
		if (j >= 0)
		{
			sum += s2[j--] = '0';
		}
		result += (sum % 10) + '0';
		carry = sum / 10;
	}

	std::reverse(result.begin(), result.end());
	return (bigint(result));
}

bigint& bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return (*this);
}

bigint& bigint::operator++()
{
	*this += 1;
	return (*this);
}

bigint bigint::operator++(int)
{
	bigint temp = *this;
	++(*this);
	return (temp);
}

// ============================

bigint bigint::operator<<(int n) const
{
	if (value_ == "0" || n <= 0)
	{
		return (*this);
	}
	return (bigint(value_ + std::string(n, '0')));
}

bigint& bigint::operator<<=(int n)
{
	if (value_ != "0" && n > 0)
	{
		value_ += std::string(n, '0');
	}
	return (*this);
}

bigint bigint::operator>>(int n) const
{
	if (n <= 0)
	{
		return (*this);
	}
	if (static_cast<size_t>(n) >= value_.length())
	{
		return (bigint(0));
	}
	return (bigint(value_.substr(0, value_.length() - n)));
}

bigint& bigint::operator>>=(int n)
{
	if (n > 0)
	{
		if (static_cast<size_t>(n) >= value_.length())
		{
			value_ = "0";
		}
		else
		{
			value_ = value_.substr(0, value_.length() - n);
		}
	}
	return (*this);
}

bigint bigint::operator<<(const bigint& n) const { return (*this << n.to_int()); }
bigint& bigint::operator<<=(const bigint& n) { return (*this <<= n.to_int()); }
bigint bigint::operator>>(const bigint& n) const { return (*this >> n.to_int()); }
bigint& bigint::operator>>=(const bigint& n) { return (*this >>= n.to_int()); }

// ============================

std::ostream& operator<<(std::ostream& os, const bigint& bi)
{
	os << bi.value_;
	return (os);
}

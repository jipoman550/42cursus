#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
public:
	bigint(unsigned long long value = 0);
	bigint(const std::string& s);
	bigint(const bigint& other);
	~bigint();

	bigint& operator=(const bigint& other);

	bool operator<(const bigint& other) const;
	bool operator==(const bigint& other) const;

	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	bool operator!=(const bigint& other) const;

	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);
	bigint& operator++();
	bigint operator++(int);

	bigint operator<<(int n) const;
	bigint& operator<<=(int n);
	bigint operator>>(int n) const;
	bigint& operator>>=(int n);

	bigint operator<<(const bigint& n) const;
	bigint& operator<<=(const bigint& n);
	bigint operator>>(const bigint& n) const;
	bigint& operator>>=(const bigint& n);

	friend std::ostream& operator<<(std::ostream& os, const bigint& bi);

private:
	std::string value_;
	void trim();
	int to_int() const;
};

#endif
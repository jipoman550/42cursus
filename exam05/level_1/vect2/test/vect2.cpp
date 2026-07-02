#include "vect2.hpp"

vect2::vect2(int x, int y)
{
	data[0] = x;
	data[1] = y;
}

vect2::vect2(const vect2& other)
{
	data[0] = other.data[0];
	data[1] = other.data[1];
}

vect2::~vect2() {}

// =========================================

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		data[0] = other.data[0];
		data[1] = other.data[1];
	}
	return (*this);
}

// =========================================

int& vect2::operator[](int index) { return (data[index]); }
const int& vect2::operator[](int index) const { return (data[index]); }

// =========================================

vect2& vect2::operator+=(const vect2& other)
{
	data[0] += other.data[0];
	data[1] += other.data[1];
	return (*this);
}

vect2& vect2::operator-=(const vect2& other)
{
	data[0] -= other.data[0];
	data[1] -= other.data[1];
	return (*this);
}

vect2& vect2::operator*=(int scaler)
{
	data[0] *= scaler;
	data[1] *= scaler;
	return (*this);
}

// =========================================

vect2& vect2::operator++()
{
	++data[0];
	++data[1];
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 temp = *this;
	++(*this);
	return (temp);
}

vect2& vect2::operator--()
{
	--data[0];
	--data[1];
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 temp = *this;
	--(*this);
	return (temp);
}

// =========================================

vect2 vect2::operator-() const
{
	return (vect2(-data[0], -data[1]));
}

// =========================================

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v[0] << ", " << v[1] << "}";
	return (os);
}

vect2 operator+(vect2 lhs, const vect2& rhs) { return (lhs += rhs); }
vect2 operator-(vect2 lhs, const vect2& rhs) { return (lhs -= rhs); }
vect2 operator*(vect2 v, int scaler) { return (v *= scaler); }
vect2 operator*(int scaler, vect2 v) { return (v *= scaler); }
bool operator==(const vect2& lhs, const vect2& rhs) { return (lhs[0] == rhs[0] && lhs[1] == rhs[1]); }
bool operator!=(const vect2& lhs, const vect2& rhs) { return !(lhs == rhs); }
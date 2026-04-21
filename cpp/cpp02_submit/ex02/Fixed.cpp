#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed() : _val(0)
{
}

Fixed::Fixed(const int n) : _val(n << _bits)
{
}

Fixed::Fixed(const float f) : _val(roundf(f * (1 << _bits)))
{
}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
	{
		this->_val = rhs.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed()
{
}


int Fixed::getRawBits(void) const
{
	return (this->_val);
}

void Fixed::setRawBits(int const raw)
{
	this->_val = raw;
}

float Fixed::toFloat(void) const
{
	return ((float)this->_val / (1 << _bits));
}

int Fixed::toInt(void) const
{
	return (this->_val >> _bits);
}

bool Fixed::operator>(const Fixed &rhs) const
{
	return (this->_val > rhs._val);
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return (this->_val < rhs._val);
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return (this->_val >= rhs._val);
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return (this->_val <= rhs._val);
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return (this->_val == rhs._val);
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return (this->_val != rhs._val);
}

Fixed Fixed::operator+(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

Fixed &Fixed::operator++(void)
{
	this->_val++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	this->_val++;
	return (tmp);
}

Fixed &Fixed::operator--(void)
{
	this->_val--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	this->_val--;
	return (tmp);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a <= b)
		return (a);
	return (b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a <= b)
		return (a);
	return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a >= b)
		return (a);
	return (b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a >= b)
		return (a);
	return (b);
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}

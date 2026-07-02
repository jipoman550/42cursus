#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
public:
	vect2(int x = 0, int y = 0);
	vect2(const vect2& other);
	~vect2();

	vect2& operator=(const vect2& other);

	int& operator[](int index);
	const int& operator[](int index) const;

	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int scaler);

	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);

	vect2 operator-() const;

private:
	int data[2];
};

std::ostream& operator<<(std::ostream& os, const vect2& v);

vect2 operator+(vect2 lhs, const vect2& rhs);
vect2 operator-(vect2 lhs, const vect2& rhs);
vect2 operator*(vect2 v, int scaler);
vect2 operator*(int scaler, vect2 v);
bool operator==(const vect2& lhs, const vect2& rhs);
bool operator!=(const vect2& lhs, const vect2& rhs);

#endif
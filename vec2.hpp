#ifndef VEC2_HPP
#define VEC2_HPP
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace ft {

struct vec2 {
	float	x;
	float	y;

	vec2() : x(0), y(0) {}

	vec2(const float &f1, const float &f2) : x(f1), y(f2) {}

	explicit vec2(const float &f) : x(f), y(f) {}

	vec2(const vec2 &rhs) : x(rhs.x), y(rhs.y) {}

	~vec2() {}

	vec2 &operator=(const vec2 &rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	float &operator[](std::size_t i) {
		switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			default:
				throw std::out_of_range("Index out of range");
		}
	}

	const float &operator[](std::size_t i) const {
		switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			default:
				throw std::out_of_range("Index out of range");
		}
	}

	vec2 operator+(const vec2 &rhs) const {
		vec2 temp(x + rhs.x, y + rhs.y);
		return (temp);
	}

	vec2 &operator+=(const vec2 &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	vec2 operator-(const vec2 &rhs) const {
		vec2 temp(x - rhs.x, y - rhs.y);
		return (temp);
	}

	vec2 &operator-=(const vec2 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	vec2 operator*(const int &i) const {
		vec2 temp(x * i, y * i);
		return temp;
	}

	vec2 &operator*=(const int &i) {
		x *= i;
		y *= i;
		return *this;
	}

	vec2 operator*(const float &f) const {
		vec2 temp(x * f, y * f);
		return temp;
	}

	vec2 &operator*=(const float &f) {
		x *= f;
		y *= f;
		return *this;
	}

	vec2 operator*(const vec2 &v) const {
		vec2 temp(x * v.x, y * v.y);
		return temp;
	}

	vec2 &operator*=(const vec2 &v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	vec2 operator/(const int &i) const {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		vec2 temp(x / i, y / i);
		return temp;
	}

	vec2 &operator/=(const int &i) {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		x /= i;
		y /= i;
		return *this;
	}

	vec2 operator/(const float &f) const {
		if (f < 1e-6)
			throw std::runtime_error("Division by zero");
		vec2 temp(x / f, y / f);
		return temp;
	}

	vec2 &operator/=(const float &f) {
		if (f < 1e-6)
			throw std::runtime_error("Division by zero");
		x /= f;
		y /= f;
		return *this;
	}

	vec2 operator/(const vec2 &rhs) const {
		if (rhs.x < 1e-6 || \
			rhs.y < 1e-6)
			throw std::runtime_error("Division by zero");
		vec2 temp(x / rhs.x, y / rhs.y);
		return temp;
	}

	vec2 &operator/=(const vec2 &rhs) {
		if (rhs.x < 1e-6 || \
			rhs.y < 1e-6)
			throw std::runtime_error("Division by zero");
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	bool operator==(const vec2 &rhs) const {
		return (x == rhs.x && y == rhs.y);
	}

	bool operator!=(const vec2 &rhs) const {
		return (!(*this == rhs));
	}

	bool operator<(const vec2 &rhs) const {
		return (this->squaredlength() < rhs.squaredlength());
	}

	bool operator<=(const vec2 &rhs) const {
		return (!(rhs < *this));
	}

	bool operator>(const vec2 &rhs) const {
		return (rhs < *this);
	}

	bool operator>=(const vec2 &rhs) const {
		return (!(*this < rhs));
	}

	float length() const {
		return std::sqrt(x*x + y*y);
	}

	float squaredlength() const {
		return x*x + y*y;
	}

	float dotproduct(const vec2 &v) const {
		return x * v.x + y * v.y;
	}

	void normalize() {
		float len = this->length();
		if (len > 1e-6)
			*this /= len;
	}

	vec2& negate() {
		x = -x;
		y = -y;
		return *this;
	}

	vec2 operator-() const {
		return vec2(-x, -y);
	}
};

inline std::ostream &operator<<(std::ostream &o, const vec2 &v) {
	o << "[" << v.x << ", " << v.y << "]";
	return o;
}

inline vec2 operator*(const int &i, const vec2 &v) {
	vec2 temp = v * i;
	return temp;
}

inline vec2 operator*(const float &f, const vec2 &v) {
	vec2 temp = v * f;
	return temp;
}

} // namespace ft
#endif
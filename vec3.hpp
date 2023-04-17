#ifndef VEC3_HPP
#define VEC3_HPP
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace ft {

struct vec3 {
	float	x;
	float	y;
	float	z;

	vec3() : x(0), y(0), z(0) {}

	vec3(const float &f1, const float &f2, const float &f3) : x(f1), y(f2), z(f3) {}

	explicit vec3(const float &f) : x(f), y(f), z(f) {}

	vec3(const vec3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

	~vec3() {}

	vec3 &operator=(const vec3 &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	float &operator[](std::size_t i) {
		switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
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
			case 2:
				return z;
			default:
				throw std::out_of_range("Index out of range");
		}
	}

	vec3 operator+(const vec3 &rhs) const {
		vec3 temp(x + rhs.x, y + rhs.y, z + rhs.z);
		return (temp);
	}

	vec3 &operator+=(const vec3 &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vec3 operator-(const vec3 &rhs) const {
		vec3 temp(x - rhs.x, y - rhs.y, z - rhs.z);
		return (temp);
	}

	vec3 &operator-=(const vec3 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	vec3 operator*(const int &i) const {
		vec3 temp(x * i, y * i, z * i);
		return temp;
	}

	vec3 &operator*=(const int &i) {
		x *= i;
		y *= i;
		z *= i;
		return *this;
	}

	vec3 operator*(const float &f) const {
		vec3 temp(x * f, y * f, z * f);
		return temp;
	}

	vec3 &operator*=(const float &f) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	vec3 operator*(const vec3 &v) const {
		vec3 temp(x * v.x, y * v.y, z * v.z);
		return temp;
	}

	vec3 &operator*=(const vec3 &v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3 operator/(const int &i) const {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		vec3 temp(x / i, y / i, z / i);
		return temp;
	}

	vec3 &operator/=(const int &i) {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		x /= i;
		y /= i;
		z /= i;
		return *this;
	}

	vec3 operator/(const float &f) const {
		if (f < 1e-6)
			throw std::runtime_error("Division by zero");
		vec3 temp(x / f, y / f, z / f);
		return temp;
	}

	vec3 &operator/=(const float &f) {
		if (f < 1e-6)
			throw std::runtime_error("Division by zero");
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	vec3 operator/(const vec3 &rhs) const {
		if (rhs.x < 1e-6 || \
			rhs.y < 1e-6 || \
			rhs.z < 1e-6)
			throw std::runtime_error("Division by zero");
		vec3 temp(x / rhs.x, y / rhs.y, z / rhs.z);
		return temp;
	}

	vec3 &operator/=(const vec3 &rhs) {
		if (rhs.x < 1e-6 || \
			rhs.y < 1e-6 || \
			rhs.z < 1e-6)
			throw std::runtime_error("Division by zero");
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	bool operator==(const vec3 &rhs) const {
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	bool operator!=(const vec3 &rhs) const {
		return (!(*this == rhs));
	}

	bool operator<(const vec3 &rhs) const {
		return (this->squaredlength() < rhs.squaredlength());
	}

	bool operator<=(const vec3 &rhs) const {
		return (!(rhs < *this));
	}

	bool operator>(const vec3 &rhs) const {
		return (rhs < *this);
	}

	bool operator>=(const vec3 &rhs) const {
		return (!(*this < rhs));
	}

	float length() const {
		return std::sqrt(x*x + y*y + z*z);
	}

	float squaredlength() const {
		return x*x + y*y + z*z;
	}

	float dotproduct(const vec3 &v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	vec3 crossproduct(const vec3 &v) const {
		vec3 temp;
		temp.x = y*v.z - z*v.y;
		temp.y = z*v.x - x*v.z;
		temp.z = x*v.y - y*v.x;
		return temp;
	}

	void normalize() {
		float len = this->length();
		if (len > 1e-6)
			*this /= len;
	}

	vec3& negate() {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	vec3 operator-() const {
		return vec3(-x, -y, -z);
	}
};

inline std::ostream &operator<<(std::ostream &o, const vec3 &v) {
	o << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return o;
}

inline vec3 operator*(const int &i, const vec3 &v) {
	vec3 temp = v * i;
	return temp;
}

inline vec3 operator*(const float &f, const vec3 &v) {
	vec3 temp = v * f;
	return temp;
}

} // namespace ft
#endif
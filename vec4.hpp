#ifndef VEC4_HPP
#define VEC4_HPP
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace ft {

struct vec4 {
	float	x;
	float	y;
	float	z;
	float	w;

	vec4() : x(0), y(0), z(0), w(0) {}

	vec4(const float &f1, const float &f2, const float &f3, const float &f4) : x(f1), y(f2), z(f3), w(f4) {}

	vec4(const float &f) : x(f), y(f), z(f), w(f) {}

	vec4(const vec4 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

	~vec4() {}

	vec4 &operator=(const vec4 &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	float &operator[](const std::size_t &i) {
		switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				throw std::out_of_range("Index out of range");
		}
	}

	const float &operator[](const std::size_t &i) const {
		switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				throw std::out_of_range("Index out of range");
		}
	}

	vec4 operator+(const vec4 &rhs) const {
		vec4 temp(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		return (temp);
	}

	vec4 &operator+=(const vec4 &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vec4 operator-(const vec4 &rhs) const {
		vec4 temp(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		return (temp);
	}

	vec4 &operator-=(const vec4 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	vec4 operator*(const int &i) const {
		vec4 temp(x * i, y * i, z * i, w * i);
		return temp;
	}

	vec4 &operator*=(const int &i) {
		x *= i;
		y *= i;
		z *= i;
		w *= i;
		return *this;
	}

	vec4 operator*(const float &f) const {
		vec4 temp(x * f, y * f, z * f, w * f);
		return temp;
	}

	vec4 &operator*=(const float &f) {
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	vec4 operator*(const vec4 &v) const {
		vec4 temp(x * v.x, y * v.y, z * v.z, w * v.w);
		return temp;
	}

	vec4 &operator*=(const vec4 &v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	vec4 operator/(const int &i) const {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		vec4 temp(x / i, y / i, z / i, w / i);
		return temp;
	}

	vec4 &operator/=(const int &i) {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		x /= i;
		y /= i;
		z /= i;
		w /= i;
		return *this;
	}

	vec4 operator/(const float &f) const {
		if (f < 1e-6)
			throw std::runtime_error("Division by zero");
		vec4 temp(x / f, y / f, z / f, w / f);
		return temp;
	}

	vec4 &operator/=(const float &f) {
		if (f < 1e-6)
			throw std::runtime_error("Division by zero");
		x /= f;
		y /= f;
		z /= f;
		w /= f;
		return *this;
	}

	vec4 operator/(const vec4 &rhs) const {
		if (rhs.x < 1e-6 || \
			rhs.y < 1e-6 || \
			rhs.z < 1e-6 || \
			rhs.w < 1e-6)
			throw std::runtime_error("Division by zero");
		vec4 temp(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		return temp;
	}

	vec4 &operator/=(const vec4 &rhs) {
		if (rhs.x < 1e-6 || \
			rhs.y < 1e-6 || \
			rhs.z < 1e-6 || \
			rhs.w < 1e-6)
			throw std::runtime_error("Division by zero");
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	bool operator==(const vec4 &rhs) const {
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
	}

	bool operator!=(const vec4 &rhs) const {
		return (!(*this == rhs));
	}

	bool operator<(const vec4 &rhs) const {
		return (this->squaredlength() < rhs.squaredlength());
	}

	bool operator<=(const vec4 &rhs) const {
		return (!(rhs < *this));
	}

	bool operator>(const vec4 &rhs) const {
		return (rhs < *this);
	}

	bool operator>=(const vec4 &rhs) const {
		return (!(*this < rhs));
	}

	float length() const {
		return std::sqrt(x*x + y*y + z*z + w*w);
	}

	float squaredlength() const {
		return x*x + y*y + z*z + w*w;
	}

	float dotproduct(const vec4 &v) const {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	void normalize() {
		float len = this->length();
		if (len > std::numeric_limits<float>::epsilon())
			*this /= len;
	}
	
	vec4& negate() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}

	vec4 operator-() const {
		return vec4(-x, -y, -z, -w);
	}
};
inline std::ostream &operator<<(std::ostream &o, const vec4 &v) {
	o << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
	return o;
}

inline vec4 operator*(const int &i, const vec4 &v) {
	vec4 temp = v * i;
	return temp;
}

inline vec4 operator*(const float &f, const vec4 &v) {
	vec4 temp = v * f;
	return temp;
}
} // namespace ft
#endif
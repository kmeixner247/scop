#ifndef MAT4_HPP
#define MAT4_HPP
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "vec3.hpp"
#include "vec4.hpp"
namespace ft {

class mat4 {
	private:
		vec4 data[4];
	public:
	mat4() {
		data[0] = vec4(1, 0, 0, 0);
		data[1] = vec4(0, 1, 0, 0);
		data[2] = vec4(0, 0, 1, 0);
		data[3] = vec4(0, 0, 0, 1);
		// data[0] = vec4();
		// data[1] = vec4();
		// data[2] = vec4();
		// data[3] = vec4();
	}
	mat4(const vec4 &v1, const vec4 &v2, const vec4 &v3, const vec4 &v4) {
		data[0] = v1;
		data[1] = v2;
		data[2] = v3;
		data[3] = v4;
	}
	mat4(const vec4 &v) {
		data[0] = v;
		data[1] = v;
		data[2] = v;
		data[3] = v;
	}
	mat4(const float &v) {
		data[0] = vec4(v, 0, 0, 0);
		data[1] = vec4(0, v, 0, 0);
		data[2] = vec4(0, 0, v, 0);
		data[3] = vec4(0, 0, 0, v);
		// data[0] = vec4(v);
		// data[1] = vec4(v);
		// data[2] = vec4(v);
		// data[3] = vec4(v);
	}
	mat4(const mat4 &rhs) {
		*this = rhs;
	}
	~mat4() {}
	mat4 &operator=(const mat4 &rhs) {
		data[0] = rhs.data[0];
		data[1] = rhs.data[1];
		data[2] = rhs.data[2];
		data[3] = rhs.data[3];
		return *this;
	}
	vec4 &operator[](std::size_t i) {
		switch (i) {
			case 0 ... 3:
				return data[i];
			default:
				throw std::out_of_range("Index out of range");
		}
	}
	const vec4 &operator[](std::size_t i) const {
		switch (i) {
			case 0 ... 3:
				return data[i];
			default:
				throw std::out_of_range("Index out of range");
		}
	}
	mat4 operator+(const mat4 &rhs) const {
		mat4 temp(data[0] + rhs[0], data[1] + rhs[1], data[2] + rhs[2], data[3] + rhs[3]);
		return (temp);
	}
	mat4 operator+=(const mat4 &rhs) {
		data[0] += rhs[0];
		data[1] += rhs[1];
		data[2] += rhs[2];
		data[3] += rhs[3];
		return *this;
	}
	mat4 operator-(const mat4 &rhs) const {
		mat4 temp(data[0] - rhs[0], data[1] - rhs[1], data[2] - rhs[2], data[3] - rhs[3]);
		return (temp);
	}
	mat4 operator-=(const mat4 &rhs) {
		data[0] -= rhs[0];
		data[1] -= rhs[1];
		data[2] -= rhs[2];
		data[3] -= rhs[3];
		return *this;
	}
	mat4 operator*(const int &i) const {
		mat4 temp(data[0] * i, data[1] * i, data[2] * i, data[3] * i);
		return temp;
	}
	mat4 operator*=(const int &i)  {
		data[0] *= i;
		data[1] *= i;
		data[2] *= i;
		data[3] *= i;
		return *this;
	}
	mat4 operator*(const float &f) const {
		mat4 temp(data[0] * f, data[1] * f, data[2] * f, data[3] * f);
		return temp;
	}

	mat4 &operator*=(const float &f) {
		data[0] *= f;
		data[1] *= f;
		data[2] *= f;
		data[3] *= f;
		return *this;
	}
	
	vec4 operator*(const vec4 &v) {
		vec4 result;
		result.x = data[0].x * v.x + data[0].y * v.y + data[0].z * v.z + data[0].w * v.w;
		result.y = data[1].x * v.x + data[1].y * v.y + data[1].z * v.z + data[1].w * v.w;
		result.z = data[2].x * v.x + data[2].y * v.y + data[2].z * v.z + data[2].w * v.w;
		result.w = data[3].x * v.x + data[3].y * v.y + data[3].z * v.z + data[3].w * v.w;
		return result;
	}

	mat4 operator/(const int &i) const {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		mat4 temp(data[0] / i, data[1] / i, data[2] / i, data[3] / i);
		return temp;
	}
	mat4 operator/=(const int &i) {
		if (i == 0)
			throw std::runtime_error("Division by zero");
		data[0] /= i;
		data[1] /= i;
		data[2] /= i;
		data[3] /= i;
		return *this;
	}
	mat4 operator/(const float &f) const {
		if (f < std::numeric_limits<float>::epsilon())
			throw std::runtime_error("Division by zero");
		mat4 temp(data[0] / f, data[1] / f, data[2] / f, data[3] / f);
		return temp;
	}
	mat4 operator/=(const float &f) {
		if (f == 0)
			throw std::runtime_error("Division by zero");
		data[0] /= f;
		data[1] /= f;
		data[2] /= f;
		data[3] /= f;
		return *this;
	}
};

inline std::ostream &operator<<(std::ostream &o, const mat4 &m) {
	o << "{" << m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << "}";
	return o;
}
inline mat4 operator*(const int &i, const mat4 &m) {
	mat4 temp = m * i;
	return temp;
}
inline mat4 operator*(const float &f, const mat4 &m) {
	mat4 temp = m * f;
	return temp;
}
} // namespace ft

#endif
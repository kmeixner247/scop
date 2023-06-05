#ifndef MATH_HPP
#define MATH_HPP
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"

namespace ft {
	inline vec3 normalize(const vec3 &v) {
		float len = v.length();
		if (len > 1e-6)
			return v / len;
		else
			throw std::runtime_error("Division by zero");
	}
	inline vec4 normalize(const vec4 &v) {
		float len = v.length();
		if (len > 1e-6)
			return v / len;
		else
			throw std::runtime_error("Division by zero");
	}

	inline float radians(const float &deg) {
		return deg * 0.01745329251994329576923690768489;
	}
	inline mat4 perspective(const float &fovy, const float &aspect, const float &near,const float &far) {
		const float temp = tan(fovy / 2.0f);

		mat4 result;
		result[0][0] = 1.0f / (aspect * temp);
		result[1][1] = 1.0f / temp;
		result[2][2] = - (far + near) / (far - near);
		result[2][3] = -1.0f;
		result[3][2] = - (2.0f * far * near) / (far - near);
		return result;
	}
	inline mat4 translate(const mat4 &m, const vec3 &v) {
		mat4 result(m);
		result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return result;
	}
	inline mat4 rotate(const mat4 &m, const float &angle, const vec3 &v) {
		const float c = cos(angle);
		const float s = sin(angle);

		vec3 axis(normalize(v));
		vec3 temp = (1.0f - c) * axis;

		mat4 rot;
		rot[0][0] = c + temp[0] * axis[0];
		rot[0][1] = temp[0] * axis[1] + s * axis[2];
		rot[0][2] = temp[0] * axis[2] - s * axis[1];

		rot[1][0] = temp[1] * axis[0] - s * axis[2];
		rot[1][1] = c + temp[1] * axis[1];
		rot[1][2] = temp[1] * axis[2] + s * axis[0];

		rot[2][0] = temp[2] * axis[0] + s * axis[1];
		rot[2][1] = temp[2] * axis[1] - s * axis[0];
		rot[2][2] = c + temp[2] * axis[2];

		mat4 result;
		result[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
		result[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
		result[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
		result[3] = m[3];
		return result;
	}

	inline mat4 scale(const mat4 &m4, const vec3 &v) {
		mat4 scaled = m4;

		scaled[0] *= v[0];
		scaled[1] *= v[1];
		scaled[2] *= v[2];
		
		return scaled;
	}

	inline vec3 crossproduct(const vec3 &v1, const vec3 &v2) {
		vec3 temp;
		temp.x = v1.y*v2.z - v1.z*v2.y;
		temp.y = v1.z*v2.x - v1.x*v2.z;
		temp.z = v1.x*v2.y - v1.y*v2.x;
		return temp;
	}
}



#endif
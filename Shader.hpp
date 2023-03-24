#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>
#include <sstream>
#include "test.hpp"
class Shader {
public:
	Shader();
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	Shader(const Shader &rhs);
	~Shader();
	Shader &operator=(const Shader &rhs);
	void use();
	unsigned int getId();
private:
	unsigned int _id;
};
#endif
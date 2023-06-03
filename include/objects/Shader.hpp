#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>
#include <sstream>
#include "../scop.hpp"
#include "../math/math.hpp"
class Shader {
public:
	Shader();
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	Shader(const Shader &rhs);
	~Shader();
	Shader &operator=(const Shader &rhs);
	void use();
	void useValue(std::string const &name, ft::vec3 const &val);
	void useValue(std::string const &name, ft::mat4 const &val);
	unsigned int getId();
private:
	unsigned int _id;
};
#endif
#ifndef SHADER_HPP
#define SHADER_HPP


#include "Material.hpp"
#include "../math/math.hpp"
#include <OpenGL/gl3.h>


#include <fstream>

class Shader {
private:
	unsigned int _id;

public:
	Shader();
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	Shader(const Shader &rhs);
	~Shader();
	Shader &operator=(const Shader &rhs);
	void use() const;
	void useMaterial(Material const &mat) const;
	void useValue(std::string const &name, float const &val) const;
	void useValue(std::string const &name, ft::vec3 const &val) const;
	void useValue(std::string const &name, ft::mat4 const &val) const;
	unsigned int getId();
};
#endif
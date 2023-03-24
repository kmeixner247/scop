#include "Shader.hpp"

Shader::Shader() : _id(0){}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
	unsigned int v, f;
	const char *vertexSource, *fragmentSource;
	std::string vertexString, fragmentString;
	try {
		std::ifstream vertexFile(vertexPath), fragmentFile(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();	
		vertexFile.close();
		fragmentFile.close();
		vertexString = vertexStream.str();
		fragmentString = fragmentStream.str();
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR: Error while reading shader files: " << e.what() << std::endl;
	}
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(v, 1, &vertexSource, NULL);
	glShaderSource(f, 1, &fragmentSource, NULL);
	
	int status;
	char infoLog[512];
	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &status);
	if(!status)
	{
		glGetShaderInfoLog(v, 512, NULL, infoLog);
		std::cerr << "ERROR: Vertex shader compilation failed\n" << infoLog << std::endl;
	};

	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &status);
	if(!status)
	{
		glGetShaderInfoLog(f, 512, NULL, infoLog);
		std::cerr << "ERROR: Fragment shader compilation failed\n" << infoLog << std::endl;
	};
	this->_id = glCreateProgram();
	glAttachShader(this->_id, v);
	glAttachShader(this->_id, f);
	glLinkProgram(this->_id);
	glGetProgramiv(this->_id, GL_LINK_STATUS, &status);
	if(!status)
	{
		glGetProgramInfoLog(this->_id, 512, NULL, infoLog);
		std::cerr << "ERROR: Shader linking failed\n" << infoLog << std::endl;
	}
	glDeleteShader(v);
	glDeleteShader(f);
}

Shader::Shader(const Shader &rhs) {
	*this = rhs;
}

Shader &Shader::operator=(const Shader &rhs) {
	this->_id = rhs._id;
	return *this;
}

Shader::~Shader() {}

void Shader::use() {
	glUseProgram(this->_id);
}

unsigned int Shader::getId(){
	return this->_id;
}
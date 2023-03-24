#ifndef GLFW_HPP
#define GLFW_HPP
#include "test.hpp"
class GLFW {
private:
	const GLint _WIDTH;
	const GLint _HEIGHT;
	const GLint _SPEED;
	GLFWwindow *_window;
	unsigned int _VBO;
	unsigned int _EBO;
	unsigned int _VAO;
public:
	GLFW(GLint WIDTH, GLint HEIGHT, GLint SPEED);
	~GLFW();
	GLFWwindow *getWindow();
	GLboolean shouldClose();
	// void processInput(t_data *data);
};
#endif
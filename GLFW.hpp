#ifndef GLFW_HPP
#define GLFW_HPP
#include "test.hpp"
class GLFW {
private:
	typedef void (*keyFunction)();
	const GLint _WIDTH;
	const GLint _HEIGHT;
	const GLint _SPEED;
	GLFWwindow *_window;
	std::map<int, keyFunction> _keyFunctions;
	void keyESC();
public:
	GLFW(GLint WIDTH, GLint HEIGHT, GLint SPEED);
	~GLFW();
	GLFWwindow *getWindow();
	GLboolean shouldClose();
	// void processInput(t_data *data);
};
#endif
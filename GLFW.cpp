#include "GLFW.hpp"

GLFW::GLFW(GLint WIDTH, GLint HEIGHT, GLint SPEED) : _WIDTH(WIDTH), _HEIGHT(HEIGHT), _SPEED(SPEED) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->_window = glfwCreateWindow(this->_WIDTH, this->_HEIGHT, "scop, now new with classes!", NULL, NULL);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(this->_window, &screenWidth, &screenHeight);
	if (!this->_window) {
		std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
		this->~GLFW();
		return ;
	}
	glfwMakeContextCurrent(this->_window);
	glViewport(0, 0, screenWidth, screenHeight);
}

void GLFW::keyESC() {
	glfwSetWindowShouldClose(this->_window, true);
}

GLFW::~GLFW() {
	glfwTerminate();
}

GLFWwindow *GLFW::getWindow() {
	return this->_window;
}

GLboolean GLFW::shouldClose() {
	return glfwWindowShouldClose(this->_window);
}

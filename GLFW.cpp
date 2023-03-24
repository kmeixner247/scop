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

GLFW::~GLFW() {
	glfwTerminate();
}

GLFWwindow *GLFW::getWindow() {
	return this->_window;
}

GLboolean GLFW::shouldClose() {
	return glfwWindowShouldClose(this->_window);
}

// void GLFW::processInput(t_data *data) {
// 	int key;
// 	key = glfwGetKey(this->_window, GLFW_KEY_ESCAPE);
// 	if (key == GLFW_PRESS)
// 		glfwSetWindowShouldClose(this->_window, true);
// 	key = glfwGetKey(this->_window, GLFW_KEY_UP);
// 	if (key == GLFW_PRESS) {
// 		data->rot[0] -= 2;
// 		if (data->rot[0] < 0)
// 			data->rot[0] += 360;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_DOWN);
// 	if (key == GLFW_PRESS) {
// 		data->rot[0] += 2;
// 		if (data->rot[0] > 360)
// 			data->rot[0] -= 360;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_LEFT);
// 	if (key == GLFW_PRESS) {
// 		data->rot[1] += 2;
// 		if (data->rot[1] > 360)
// 			data->rot[1] -= 360;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_RIGHT);
// 	if (key == GLFW_PRESS) {
// 		data->rot[1] -= 2;
// 		if (data->rot[1] < 0)
// 			data->rot[1] += 360;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_R);
// 	if (key == GLFW_PRESS) {
// 		data->rot[2] += 2;
// 		if (data->rot[2] > 360)
// 			data->rot[2] -= 360;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_T);
// 	if (key == GLFW_PRESS) {
// 		data->rot[2] -= 2;
// 		if (data->rot[2] < 0)
// 			data->rot[2] += 360;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_W);
// 	if (key == GLFW_PRESS) {
// 		data->mov[1] -= this->_SPEED;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_S);
// 	if (key == GLFW_PRESS) {
// 		data->mov[1] += this->_SPEED;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_A);
// 	if (key == GLFW_PRESS) {
// 		data->mov[0] += this->_SPEED;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_D);
// 	if (key == GLFW_PRESS) {
// 		data->mov[0] -= this->_SPEED;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_I);
// 	if (key == GLFW_PRESS) {
// 		data->mov[2] += this->_SPEED;
// 	}
// 	key = glfwGetKey(this->_window, GLFW_KEY_O);
// 	if (key == GLFW_PRESS) {
// 		data->mov[2] -= this->_SPEED;
// 	}
// }
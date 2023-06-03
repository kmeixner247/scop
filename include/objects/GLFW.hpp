#pragma once

#include "../scop.hpp"
class GLFW {
private:
	typedef void (GLFW::*keyFunction)();
	const GLint _WIDTH;
	const GLint _HEIGHT;
	const GLfloat _SPEED;
	GLFWwindow *_window;
	ft::mat4 _rot;
	float _mov[3];
	std::map<int, keyFunction> _keyMap;
	void keyESC() { glfwSetWindowShouldClose(this->_window, true); }
	void keyUP() { this->rotate(-2.0, 0); }
	void keyDOWN() { this->rotate(2.0, 0); }
	void keyLEFT() { this->rotate(2.0, 1); }
	void keyRIGHT() { this->rotate(-2.0, 1); }
	void keyR() { this->rotate(2.0, 2); }
	void keyT() { this->rotate(-2.0, 2); }
	void keyD() { this->_mov[0] -= this->_SPEED; }
	void keyA() { this->_mov[0] += this->_SPEED; }
	void keyW() { this->_mov[1] -= this->_SPEED; }
	void keyS() { this->_mov[1] += this->_SPEED; }
	void keyO() { this->_mov[2] -= this->_SPEED; }
	void keyI() { this->_mov[2] += this->_SPEED; }
	void rotate(float angle, int mode);
public:
	GLFW(GLint WIDTH, GLint HEIGHT, GLfloat SPEED);
	~GLFW() { glfwTerminate(); }
	GLFWwindow *getWindow() { return this->_window; }
	ft::mat4 getRot() { return this->_rot; }
	float getMov(int ind) { return this->_mov[ind]; }
	GLboolean shouldClose() { return glfwWindowShouldClose(this->_window); }
	void processInput();
};

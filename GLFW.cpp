#include "GLFW.hpp"

GLFW::GLFW(GLint WIDTH, GLint HEIGHT, GLfloat SPEED) : _WIDTH(WIDTH), _HEIGHT(HEIGHT), _SPEED(SPEED) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->_window = glfwCreateWindow(this->_WIDTH, this->_HEIGHT, "spooky shadows", NULL, NULL);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(this->_window, &screenWidth, &screenHeight);
	if (!this->_window) {
		std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
		this->~GLFW();
		return ;
	}
	glfwMakeContextCurrent(this->_window);
	glViewport(0, 0, screenWidth, screenHeight);
	this->_rot = ft::mat4(1.0f);
	// initializing key map
	_keyMap[GLFW_KEY_ESCAPE] = &GLFW::keyESC;
	_keyMap[GLFW_KEY_UP] = &GLFW::keyUP;
	_keyMap[GLFW_KEY_DOWN] = &GLFW::keyDOWN;
	_keyMap[GLFW_KEY_LEFT] = &GLFW::keyLEFT;
	_keyMap[GLFW_KEY_RIGHT] = &GLFW::keyRIGHT;
	_keyMap[GLFW_KEY_R] = &GLFW::keyR;
	_keyMap[GLFW_KEY_T] = &GLFW::keyT;
	_keyMap[GLFW_KEY_W] = &GLFW::keyW;
	_keyMap[GLFW_KEY_S] = &GLFW::keyS;
	_keyMap[GLFW_KEY_A] = &GLFW::keyA;
	_keyMap[GLFW_KEY_D] = &GLFW::keyD;
	_keyMap[GLFW_KEY_I] = &GLFW::keyI;
	_keyMap[GLFW_KEY_O] = &GLFW::keyO;
	_mov[0] = 0;
	_mov[1] = 0;
	_mov[2] = 0;
}

void GLFW::rotate(float angle, int mode)
{
    // mode 0 for X, 1 for Y, 2 for Z
    ft::vec3 axis;
    axis[mode] = 1.0f;
    this->_rot = ft::rotate(this->_rot, ft::radians(angle), axis);
}

void GLFW::processInput() {
	std::map<int, GLFW::keyFunction>::iterator it = this->_keyMap.begin();
	for (;it != this->_keyMap.end(); it++) {
		if (glfwGetKey(this->_window, it->first) == GLFW_PRESS) {
			GLFW::keyFunction func = it->second;
			(this->*func)();
		} 
	}
}
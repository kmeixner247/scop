#include "../../include/objects/Window.hpp"

Window::Window(GLint WIDTH, GLint HEIGHT, GLfloat SPEED) : _WIDTH(WIDTH), _HEIGHT(HEIGHT), _SPEED(SPEED) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->_window = glfwCreateWindow(this->_WIDTH, this->_HEIGHT, "scop", NULL, NULL);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(this->_window, &screenWidth, &screenHeight);
	if (!this->_window) {
		std::cerr << "ERROR: Failed to create Window window" << std::endl;
		this->~Window();
		return ;
	}
	glfwMakeContextCurrent(this->_window);
	glViewport(0, 0, screenWidth, screenHeight);
	this->_rot = ft::mat4(1.0f);
	// initializing key map
	_keyMap[GLFW_KEY_ESCAPE] = &Window::keyESC;
	_keyMap[GLFW_KEY_UP] = &Window::keyUP;
	_keyMap[GLFW_KEY_DOWN] = &Window::keyDOWN;
	_keyMap[GLFW_KEY_LEFT] = &Window::keyLEFT;
	_keyMap[GLFW_KEY_RIGHT] = &Window::keyRIGHT;
	_keyMap[GLFW_KEY_R] = &Window::keyR;
	_keyMap[GLFW_KEY_T] = &Window::keyT;
	_keyMap[GLFW_KEY_W] = &Window::keyW;
	_keyMap[GLFW_KEY_S] = &Window::keyS;
	_keyMap[GLFW_KEY_A] = &Window::keyA;
	_keyMap[GLFW_KEY_D] = &Window::keyD;
	_keyMap[GLFW_KEY_I] = &Window::keyI;
	_keyMap[GLFW_KEY_O] = &Window::keyO;
	_keyMap[GLFW_KEY_K] = &Window::keyK;
	_keyMap[GLFW_KEY_L] = &Window::keyL;
	_mov[0] = 0;
	_mov[1] = 0;
	_mov[2] = 0;
}

void Window::rotate(float angle, int mode)
{
    // mode 0 for X, 1 for Y, 2 for Z
    ft::vec3 axis;
    axis[mode] = 1.0f;
    this->_rot = ft::rotate(this->_rot, ft::radians(angle), axis);
}

Window::~Window() {
	glfwTerminate();
}

GLFWwindow *Window::getWindow() const {
	return this->_window;
}

ft::mat4 Window::getRot() const {
	return this->_rot;
}

float Window::getMov(int const &ind)
{
	return this->_mov[ind];
}

void Window::processInput(Scene &scene) {
	std::map<int, Window::keyFunction>::iterator it = this->_keyMap.begin();
	for (;it != this->_keyMap.end(); it++) {
		if (glfwGetKey(this->_window, it->first) == GLFW_PRESS) {
			Window::keyFunction func = it->second;
			(this->*func)(scene);
		} 
	}
}

GLboolean Window::shouldClose() {
	return glfwWindowShouldClose(this->_window);
}

GLint Window::getWidth() const {
	return _WIDTH;
}

GLint Window::getHeight() const {
	return _HEIGHT;
}

void Window::clear(ft::vec4 const &color) {
	glClearColor(color[0], color[1], color[2], color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#pragma once

#include "../scop.hpp"
#include "Scene.hpp"
class Window {
private:
	typedef void (Window::*keyFunction)(Scene&);
	const GLint _WIDTH;
	const GLint _HEIGHT;
	const GLfloat _SPEED;
	GLFWwindow *_window;
	ft::mat4 _rot;
	float _mov[3];
	std::map<int, keyFunction> _keyMap;
	void keyESC(Scene &scene) { (void)scene; glfwSetWindowShouldClose(this->_window, true); }
	void keyUP(Scene &scene) { scene.rotateObjects(-2.0, 0); }
	void keyDOWN(Scene &scene) { scene.rotateObjects(2.0, 0); }
	void keyLEFT(Scene &scene) { scene.rotateObjects(2.0, 1); }
	void keyRIGHT(Scene &scene) { scene.rotateObjects(-2.0, 1); }
	void keyR(Scene &scene) { scene.rotateObjects(2.0, 2); }
	void keyT(Scene &scene) { scene.rotateObjects(-2.0, 2); }
	void keyD(Scene &scene) { scene.moveCamera(ft::vec3(this->_SPEED, 0, 0)); }
	void keyA(Scene &scene) { scene.moveCamera(ft::vec3(-this->_SPEED, 0, 0)); }
	void keyW(Scene &scene) { scene.moveCamera(ft::vec3(0, this->_SPEED, 0)); }
	void keyS(Scene &scene) { scene.moveCamera(ft::vec3(0, -this->_SPEED, 0)); }
	void keyO(Scene &scene) { scene.moveCamera(ft::vec3(0, 0, this->_SPEED)); }
	void keyI(Scene &scene) { scene.moveCamera(ft::vec3(0, 0, -this->_SPEED)); }
	void keyK(Scene &scene) { scene.scale(1.05); }
	void keyL(Scene &scene) { scene.scale(0.95); }
	void key1(Scene &scene) { scene.switchShader(0); }
	void key2(Scene &scene) { scene.switchShader(1); }
	void keyTab(Scene &scene) { scene.transitionTexture(); }

	void rotate(float angle, int mode);

	Window() : _WIDTH(0), _HEIGHT(0), _SPEED(0) {}
	Window(Window const &rhs) : _WIDTH(0), _HEIGHT(0), _SPEED(0) { *this = rhs; }
	Window &operator=(Window const &rhs) { (void)rhs; return *this; }
public:
	Window(GLint WIDTH, GLint HEIGHT, GLfloat SPEED);
	~Window();
	GLFWwindow *getWindow() const;
	ft::mat4 getRot() const;
	float getMov(int const &ind);
	void processInput(Scene &scene);
	GLboolean shouldClose();
	GLint getWidth() const;
	GLint getHeight() const;
	void clear(ft::vec4 const &color);
};

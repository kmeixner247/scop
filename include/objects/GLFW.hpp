#pragma once

#include "../scop.hpp"
#include "Scene.hpp"
class GLFW {
private:
	typedef void (GLFW::*keyFunction)(Scene&);
	const GLint _WIDTH;
	const GLint _HEIGHT;
	const GLfloat _SPEED;
	GLFWwindow *_window;
	ft::mat4 _rot;
	float _mov[3];
	std::map<int, keyFunction> _keyMap;
	void keyESC(Scene &scene) { glfwSetWindowShouldClose(this->_window, true); }
	void keyUP(Scene &scene) { this->rotate(-2.0, 0); }
	void keyDOWN(Scene &scene) { this->rotate(2.0, 0); }
	void keyLEFT(Scene &scene) { this->rotate(2.0, 1); }
	void keyRIGHT(Scene &scene) { this->rotate(-2.0, 1); }
	void keyR(Scene &scene) { this->rotate(2.0, 2); }
	void keyT(Scene &scene) { this->rotate(-2.0, 2); }
	void keyD(Scene &scene) { scene.moveCamera(ft::vec3(this->_SPEED, 0, 0)); }
	void keyA(Scene &scene) { scene.moveCamera(ft::vec3(-this->_SPEED, 0, 0)); }
	void keyW(Scene &scene) { scene.moveCamera(ft::vec3(0, this->_SPEED, 0)); }
	void keyS(Scene &scene) { scene.moveCamera(ft::vec3(0, -this->_SPEED, 0)); }
	void keyO(Scene &scene) { scene.moveCamera(ft::vec3(0, 0, this->_SPEED)); }
	void keyI(Scene &scene) { scene.moveCamera(ft::vec3(0, 0, -this->_SPEED)); }
	void rotate(float angle, int mode);
public:
	GLFW(GLint WIDTH, GLint HEIGHT, GLfloat SPEED);
	~GLFW() { glfwTerminate(); }
	GLFWwindow *getWindow() { return this->_window; }
	ft::mat4 getRot() { return this->_rot; }
	float getMov(int ind) { return this->_mov[ind]; }
	GLboolean shouldClose() { return glfwWindowShouldClose(this->_window); }
	void processInput(Scene &scene);
};

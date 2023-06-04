#include "../include/scop.hpp"
#include "../include/objects/GLFW.hpp"
#include "../include/objects/WavefrontLoader.hpp"
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.05;
#include <iostream>

int main() {
	GLFW GLFW(WIDTH, HEIGHT, MOV_SPEED);
	WavefrontLoader temp("resources/42_textured.obj");
	Shader shader("vertexshader.glsl", "fragmentshader.glsl");
    Scene myScene;

	myScene.loadObjects(temp);
	myScene.center();
	myScene.scale(2.0);
	myScene.loadMtllib(temp);
    myScene.bind();
	glEnable(GL_DEPTH_TEST);
	ft::mat4 view;
	ft::mat4 proj = ft::perspective(ft::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	ft::mat4 test(1.0f);
	ft::vec3 testvec(0,0,-3.0f);
	test = ft::translate(test, -testvec);
	std::cout << myScene.getCameraPos();
	// std::cout << test << std::endl;
    while (!GLFW.shouldClose()) {
        GLFW.processInput(myScene);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		view = ft::translate(ft::mat4(1.0f), -myScene.getCameraPos());
		int lightPosLocation = glGetUniformLocation(shader.getId(), "lightPos");
		glUniform3f(lightPosLocation, 1.5f, 0.0f, -1.5f);
		int viewPosLocation = glGetUniformLocation(shader.getId(), "viewPos");
        shader.useValue("view", view);
        shader.useValue("viewPos", myScene.getCameraPos());
        shader.useValue("proj", proj);
        shader.useValue("model", GLFW.getRot());
        myScene.draw(shader);
		glfwPollEvents();
		glfwSwapBuffers(GLFW.getWindow());
    }
}

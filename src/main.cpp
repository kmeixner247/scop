#include "../include/scop.hpp"
#include "../include/objects/Scene.hpp"
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
	myScene.loadMtllib(temp);
    myScene.bind();
	glEnable(GL_DEPTH_TEST);

	ft::mat4 view;
	ft::mat4 proj = ft::perspective(ft::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);


    while (!GLFW.shouldClose()) {
        GLFW.processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view = ft::mat4(1.0f);
		ft::vec3 asdf(GLFW.getMov(0), GLFW.getMov(1), GLFW.getMov(2) - 1.0f);
		std::cout << asdf << std::endl;
		view = ft::translate(view, asdf);
		int lightPosLocation = glGetUniformLocation(shader.getId(), "lightPos");
		glUniform3f(lightPosLocation, 0.0f, 0.0f, 1.5f);
		int viewPosLocation = glGetUniformLocation(shader.getId(), "viewPos");
        shader.useValue("view", view);
        shader.useValue("viewPos", asdf);
        shader.useValue("proj", proj);
        shader.useValue("model", GLFW.getRot());

    	// shader.use();
        myScene.draw(shader);
		glfwPollEvents();
		glfwSwapBuffers(GLFW.getWindow());
    }
}

#include "../include/scop.hpp"
#include "../include/objects/Window.hpp"
#include "../include/objects/WavefrontLoader.hpp"
#include "../include/objects/Texture.hpp"
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.05;
#include <iostream>

int main() {
	Window Window(WIDTH, HEIGHT, MOV_SPEED);
	WavefrontLoader temp("resources/textured_teapot.obj");
	Texture texture("resources/bluetexture.bmp");
	Shader shader("vertexshader.glsl", "fragmentshader.glsl");
    Scene myScene;

	myScene.init(WIDTH, HEIGHT);
	myScene.setLightPos(ft::vec3(0.5, 0, 2));
	myScene.loadObjects(temp);
	myScene.scaleTo(2);
	myScene.loadMtllib(temp);
    myScene.bind();

	texture.bind();

    while (!Window.shouldClose()) {
        Window.processInput(myScene);
		Window.clear(ft::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        myScene.draw(shader);
		glfwPollEvents();
		glfwSwapBuffers(Window.getWindow());
    }
}

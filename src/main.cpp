#include "../include/scop.hpp"
#include "../include/objects/Window.hpp"
#include "../include/objects/WavefrontLoader.hpp"
#include "../include/objects/Texture.hpp"
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.05;
#include <iostream>

int main() {
	WavefrontLoader wavefrontData("resources/42_busted.obj");
	Window Window(WIDTH, HEIGHT, MOV_SPEED);
	Texture texture("resources/Carbon_02.bmp");
	Shader simpleShader("simple_vertexshader.glsl", "simple_fragmentshader.glsl");
	Shader lightingShader("lighting_vertexshader.glsl", "lighting_fragmentshader.glsl");
    Scene myScene;

	myScene.init(WIDTH, HEIGHT);
	myScene.loadObjects(wavefrontData);
	myScene.loadMtllib(wavefrontData);
	myScene.addShader(simpleShader);
	myScene.addShader(lightingShader);
	myScene.setLightPos(ft::vec3(0.5, 0, 2));
	myScene.scaleTo(2);
    myScene.bind();
	texture.bind();

    while (!Window.shouldClose()) {
		glfwSwapInterval(1);
        Window.processInput(myScene);
		Window.clear(ft::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        myScene.draw();
		glfwPollEvents();
		glfwSwapBuffers(Window.getWindow());
    }
}

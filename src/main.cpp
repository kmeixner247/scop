#include "../include/objects/Window.hpp"
#include "../include/objects/WavefrontLoader.hpp"
#include "../include/objects/Texture.hpp"
#include <iostream>
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.05;

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Please specify an object file (.obj) and a texture file (.bmp)" << std::endl;
		return -1;
	}
	WavefrontLoader wavefrontData(argv[1]);
	Window Window(WIDTH, HEIGHT, MOV_SPEED);
	Texture texture(argv[2]);
	Shader simpleShader("simple_vertexshader.glsl", "simple_fragmentshader.glsl");
	Shader lightingShader("lighting_vertexshader.glsl", "lighting_fragmentshader.glsl");
    Scene myScene;

	myScene.init(WIDTH, HEIGHT);
	myScene.loadObjects(wavefrontData);
	myScene.loadMtllib(wavefrontData);
	myScene.addShader(simpleShader);
	myScene.addShader(lightingShader);
	myScene.setLightPos(ft::vec3(1, 0, 1));
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

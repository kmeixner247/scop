#include "../include/scop.hpp"
#include "../include/objects/GLFW.hpp"
#include "../include/objects/WavefrontLoader.hpp"
#include "../include/bmpParser.hpp"
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.05;
#include <iostream>

int main() {
	GLFW GLFW(WIDTH, HEIGHT, MOV_SPEED);
	WavefrontLoader temp("resources/textured_teapot.obj");
	Shader shader("vertexshader.glsl", "fragmentshader.glsl");
    Scene myScene;

	myScene.loadObjects(temp);
	myScene.scaleTo(2);
	myScene.loadMtllib(temp);
    myScene.bind();
	glEnable(GL_DEPTH_TEST);
	ft::mat4 view;
	ft::mat4 proj = ft::perspective(ft::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);


	// NEW TEXTURE BLOCK START
	t_bmp txt;
	// txt = parseBmp("resources/TallGreenGrass.bmp");
	txt = parseBmp("resources/RoyalTartanSmall.bmp");
	unsigned int texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture); 
	int twidth, theight, nrChannels;
	twidth = txt.dibHeader.width;
	theight = txt.dibHeader.height;
	char *tdata = reinterpret_cast<char*>(&txt.pixelData[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	// NEW TEXTURE BLOCK END
	float textureRandomRatio = 0.0f;
	float ratioChange = 0.01f;


    while (!GLFW.shouldClose()) {
		if (textureRandomRatio >= 1)
			ratioChange = -0.003f;
		if (textureRandomRatio <= 0)
			ratioChange = 0.003f;
		textureRandomRatio += ratioChange;
		shader.useValue("textureRandomRatio", textureRandomRatio);
        GLFW.processInput(myScene);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		view = ft::translate(ft::mat4(1.0f), -myScene.getCameraPos());
		int lightPosLocation = glGetUniformLocation(shader.getId(), "lightPos");
		glUniform3f(lightPosLocation, 1.5f, 1.5f, -1.5f);
		int viewPosLocation = glGetUniformLocation(shader.getId(), "viewPos");
        shader.useValue("view", view);
        shader.useValue("viewPos", myScene.getCameraPos());
        shader.useValue("proj", proj);
		glBindTexture(GL_TEXTURE_2D, texture);
        myScene.draw(shader);
		glfwPollEvents();
		glfwSwapBuffers(GLFW.getWindow());
    }
}

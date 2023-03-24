#include <OpenGL/gl3.h>
#include "include/glfw3.h"
#include <iostream>
//c++ triangles.cpp libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1
const GLint WIDTH = 800, HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor; // specify a color output to the fragment shader\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor; // we set this variable in the OpenGL code.\n"
"void main()\n"
"{\n"
"    FragColor = ourColor;\n"
"}\0";

void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 
}

GLFWwindow *createWindow() {
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "justgivemeafuckingwindow", nullptr, nullptr); 
	int screenWidth, screenHeight;
	glfwGetFramebufferSize( window, &screenWidth, &screenHeight ); 
	if (nullptr == window) 
	{ 
		std::cout << "Failed to create GLFW window" << std::endl; 
		glfwTerminate(); 
		exit(EXIT_FAILURE); 
	} 
	glfwMakeContextCurrent(window); 
   // Define the viewport dimensions 
	glViewport(0, 0, screenWidth, screenHeight);
	return window;
}

void processInput(GLFWwindow *window)
{
	int key = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if(key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int createShader(unsigned int type, const char *src) {
	unsigned int i = glCreateShader(type);
	glShaderSource(i, 1, &src, NULL);
	glCompileShader(i);
	int  success;
	char infoLog[512];
	glGetShaderiv(i, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(i, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return (i);
}

void terminate() {
	glfwTerminate();
}

int main() {
	init();
	GLFWwindow *window = createWindow();

	//TEMP BLOCK START
	// Create vertex and fragment shader
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	// Create shader program by combining both
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Delete shader objects as they're not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); 
	glLinkProgram(shaderProgram);

	float vertices[] = {
		0.232406,-1.216630,1.133818,
		0.232406,-0.745504,2.843098,
		-0.227475,-0.745504,2.843098,
		-0.227475,-1.216630,1.133818,
		0.232407,1.119982,1.133819,
		0.232406,1.119982,1.602814,
		-0.227475,1.119982,1.602813,
		-0.227475,1.119982,1.133818,
		0.232406,-0.340316,2.843098,
		-0.227475,-0.340316,2.843098,
		0.232407,-0.305193,1.133819,
		0.232407,-0.294496,2.297937,
		-0.227475,-0.305193,1.133818,
		-0.227475,-0.294496,2.297937,
		0.232406,-1.222569,1.497195,
		0.232406,-0.745504,1.477731,
		-0.227475,-0.745504,1.477731,
		-0.227475,-1.222569,1.497194,
		-0.227403,-0.731178,0.901477,
		-0.227403,-0.731178,-0.037620,
		0.223704,-0.731178,-0.037620,
		0.223704,-0.731178,0.901477,
		-0.227403,1.119377,0.901477,
		-0.227403,1.119377,-0.037620,
		0.223704,1.119377,-0.037620,
		0.223704,1.119377,0.901477,
		-0.227403,-0.129772,0.901477,
		-0.227403,0.551492,0.384487,
		-0.227403,1.104268,0.408501,
		-0.227403,0.507336,0.901477,
		0.223704,0.507336,0.901477,
		0.223704,1.104269,0.408501,
		0.223704,0.551492,0.384487,
		0.223704,-0.129772,0.901477,
		-0.227403,0.634134,-0.037620,
		-0.227403,-0.066768,0.398575,
		-0.227403,-0.684649,0.389681,
		-0.227403,-0.075523,-0.037620,
		0.223704,0.634134,-0.037620,
		0.223704,-0.066768,0.398575,
		0.223704,-0.684649,0.389681,
		0.223704,-0.075523,-0.037620,
	};
	unsigned int indices[] = {
		16,2,3,17,
		5,8,7,6,
		29,30,23,
		9,6,7,10,
		14,13,17,
		11,1,4,13,
		2,9,10,3,
		5,12,14,8,
		12,11,13,14,
		1,15,18,4,
		15,16,17,18,
		38,42,21,20,
		33,39,25,32,
		34,27,19,22,
		19,20,21,22,
		26,25,24,23,
		26,23,30,31,
		31,30,29,32,
		32,29,28,33,
		33,28,27,34,
		24,25,39,35,
		35,39,40,36,
		36,40,41,37,
		37,41,42,38,
		26,31,32,
		37,38,20,
		21,42,41,
		12,5,6,
		25,26,32,
		22,21,41,
		8,14,7,
		28,36,27,
		10,14,17,3,
		33,40,39,
		40,33,34,
		11,16,15,1,
		14,10,7,
		2,16,12,9,
		11,12,16,
		40,34,22,41,
		12,6,9,
		18,17,13,4,
		36,28,35,
		37,20,19,
		29,23,24,
		19,27,36,37,
		24,35,28,29,
	};
	// for (int i=0; i<10932; i++)
	// 	vertices[i] /= 4;
	for (int i=0; i<170; i++)
		indices[i] -= 1;
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	//TEMP BLOCK END
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Render
		glUseProgram(shaderProgram);

		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 18960, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//END
		glfwPollEvents(); 
		glfwSwapBuffers(window);
	}

	terminate();
}
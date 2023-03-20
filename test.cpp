#include "include/glfw3.h"
#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void processInput(GLFWwindow *window)
{
	int key = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if(key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



int main(void)
{
	// Window dimensions 
	const GLint WIDTH = 800, HEIGHT = 600; 
   // Init GLFW 
   glfwInit(); 
	// Set all the required options for GLFW 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

	// Create a GLFWwindow object that we can use for GLFW's functions 
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "justgivemeafuckingwindow", nullptr, nullptr); 
	int screenWidth, screenHeight; 
	glfwGetFramebufferSize( window, &screenWidth, &screenHeight ); 
	if (nullptr == window) 
	{ 
		std::cout << "Failed to create GLFW window" << std::endl; 
		glfwTerminate(); 

		return EXIT_FAILURE; 
	} 
	glfwMakeContextCurrent(window); 
   // Define the viewport dimensions 
	glViewport(0, 0, screenWidth, screenHeight);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  


	while (!glfwWindowShouldClose(window)) 
	{ 
		// Check if any events have been activiated (key pressed, 
		//mouse moved etc.) and call corresponding response functions 
		processInput(window);
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 
		// Render 
		// 0. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 1. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);  
		// 2. use our shader program when we want to render an object
		glUseProgram(shaderProgram);
		// 3. now draw the object 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Clear the colorbuffer 
	
		// Draw OpenGL 
		glfwPollEvents(); 
		glfwSwapBuffers(window); 
	}
	glfwTerminate();
}
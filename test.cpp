#include <OpenGL/gl3.h>
#include "include/glfw3.h"
#include <iostream>

float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f,   // top left 
	0.8f, 0.8f, 0.0f,
	0.7f, 0.8f, 0.0f,
	0.7f,0.7f,0.0f
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3,    // second triangle
	4,5,6
};  
// unsigned int indices1[] = {  // note that we start from 0!
// 	0, 1, 3,   // first triangle
// };  
// unsigned int indices1[] = {  // note that we start from 0!
// 	1, 2, 3    // second triangle
// };  
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
"    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

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
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glLinkProgram(shaderProgram);
	// glUseProgram(shaderProgram);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	
	while (!glfwWindowShouldClose(window)) 
	{ 
		// Chec k if any events have been activiated (key pressed, 
		//mouse moved etc.) and call corresponding response functions 
		processInput(window);
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 
		// Render 
		// Clear the colorbuffer 
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(GLuint)));
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (void*)(6*sizeof(GLuint)));
		glBindVertexArray(0);
		// Draw OpenGL 
		glfwPollEvents(); 
		glfwSwapBuffers(window); 
	}
	glfwTerminate();
}
#include "test.hpp"
// c++ parsetest.cpp parse.cpp libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1
const GLint WIDTH = 1600, HEIGHT = 1200;
void parse(char *filename, t_data *data);

std::string readShaderFile(std::string filename, t_data *data)
{
	std::ifstream infile(filename);
	std::string line, file;
	while (infile)
	{
		std::getline(infile, line);
		if (infile)
			file += line + "\n";
	}
	return file;
}

void init(t_data *data)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	data->rot[0] = 0;
	data->rot[1] = 0;
	data->rot[2] = 0;
	data->vertexShaderSource = readShaderFile("vertexshader.glsl", data);
	data->fragmentShaderSource = readShaderFile("fragmentshader.glsl", data);
}

GLFWwindow *createWindow()
{
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "fine I'm changing the name", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
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

void processInput(GLFWwindow *window, t_data *data)
{
	int key;
	key = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if (key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	key = glfwGetKey(window, GLFW_KEY_UP);
	if (key == GLFW_PRESS) {
		data->rot[0] -= 2;
		if (data->rot[0] < 0)
			data->rot[0] += 360;
	}
	key = glfwGetKey(window, GLFW_KEY_DOWN);
	if (key == GLFW_PRESS) {
		data->rot[0] += 2;
		if (data->rot[0] > 360)
			data->rot[0] -= 360;
	}
	key = glfwGetKey(window, GLFW_KEY_LEFT);
	if (key == GLFW_PRESS) {
		data->rot[1] += 2;
		if (data->rot[1] > 360)
			data->rot[1] -= 360;
	}
	key = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (key == GLFW_PRESS) {
		data->rot[1] -= 2;
		if (data->rot[1] < 0)
			data->rot[1] += 360;
	}
	key = glfwGetKey(window, GLFW_KEY_R);
	if (key == GLFW_PRESS) {
		data->rot[2] += 2;
		if (data->rot[2] > 360)
			data->rot[2] -= 360;
	}
	key = glfwGetKey(window, GLFW_KEY_T);
	if (key == GLFW_PRESS) {
		data->rot[2] -= 2;
		if (data->rot[2] < 0)
			data->rot[2] += 360;
	}
}

unsigned int createShader(unsigned int type, const char *src)
{
	unsigned int i = glCreateShader(type);
	glShaderSource(i, 1, &src, NULL);
	glCompileShader(i);
	int success;
	char infoLog[512];
	glGetShaderiv(i, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(i, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	return (i);
}

void terminate()
{
	glfwTerminate();
}

void normalize_delete_this(std::vector<float> *vertices)
{
	float max = *(std::max_element(vertices->begin(), vertices->end()));
	float min = *(std::min_element(vertices->begin(), vertices->end()));
	float factor = (min * -1 > max) ? 0.9 / min : 0.9 / max;
	// std::cerr << factor << std::endl;
	for (std::vector<float>::iterator it = vertices->begin(); it != vertices->end(); it++)
		*it *= factor;
}

void rotX(float a, float mat[4][4])
{
	a = a * (M_PI / 180);
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = cos(a);
	mat[1][2] = sin(a) * -1;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = sin(a);
	mat[2][2] = cos(a);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}
void rotY(float a, float mat[4][4])
{
	a = a * (M_PI / 180);
	mat[0][0] = cos(a);
	mat[0][1] = 0;
	mat[0][2] = sin(a);
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = sin(a) * -1;
	mat[2][1] = 0;
	mat[2][2] = cos(a);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}
void rotZ(float a, float mat[4][4])
{
	a = a * (M_PI / 180);
	mat[0][0] = cos(a);
	mat[0][1] = sin(a) * -1;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = sin(a);
	mat[1][1] = cos(a);
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

int main()
{
	t_data data;
	std::string path("resources/teapot2.obj");
	// char *path = "resources/teapot2.obj";
	init(&data);
	parse(path, &data);
	normalize_delete_this(&(data.v_vertices));
	// for (std::vector<float>::iterator it = data.v_vertices.begin(); it != data.v_vertices.end(); it++)
	// 	(*it) /= 4;
	// std::cerr << data.v_faces.size() << std::endl;
	// std::cerr << data.v_vertices.size() << std::endl;
	// std::cerr << data.v_indices.size() << std::endl;
	// for (std::vector<t_face>::iterator it = data.v_faces.begin(); it != data.v_faces.end(); it++)
	// 	std::cerr << (*it).size;
	// std::cerr << std::endl;
	// std::cerr << *(std::max_element(data.v_vertices.begin(), data.v_vertices.end())) << std::endl;
	// std::cerr << *(std::min_element(data.v_vertices.begin(), data.v_vertices.end())) << std::endl;
	GLFWwindow *window = createWindow();

	// TEMP BLOCK START
	//  Create vertex and fragment shader
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, data.vertexShaderSource.c_str());
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, data.fragmentShaderSource.c_str());
	// Create shader program by combining both
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Delete shader objects as they're not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glLinkProgram(shaderProgram);

	// for (int i=0; i<10932; i++)
	// 	vertices[i] /= 4;
	// for (int i=0; i<18960; i++)
	// 	indices[i] -= 1;
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.v_vertices.size() * sizeof(float), &(data.v_vertices[0]), GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.v_indices.size() * sizeof(int), &(data.v_indices[0]), GL_STATIC_DRAW);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.v_indices.size() * sizeof(int), &(data.v_indices[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// float transformX[4][4] = {
	// 	{1, 0, 0, 0},
	// 	{0, 0.8660, -0.5, 0},
	// 	{0, 0.5, 0.8660, 0},
	// 	{0, 0, 0, 1}};
	// float transformY[4][4] = {
	// 	{0.8660, 0, 0.5, 0},
	// 	{0, 1, 0, 0},
	// 	{-0.5, 0, 0.8660, 0},
	// 	{0, 0, 0, 1}};
	// float transformZ[4][4] = {
	// 	{0.8660, -0.5, 0, 0},
	// 	{0.5, 0.8660, 0, 0},
	// 	{0, 0, 1, 0},
	// 	{0, 0, 0, 1}};
	float transformX[4][4];
	float transformY[4][4];
	float transformZ[4][4];
	// TEMP BLOCK END
	while (!glfwWindowShouldClose(window))
	{
		processInput(window, &data);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Render
		glUseProgram(shaderProgram);
		// translate += 0.001;
		rotX(data.rot[0], transformX);
		rotY(data.rot[1], transformY);
		rotZ(data.rot[2], transformZ);
		int rotXLocation = glGetUniformLocation(shaderProgram, "rotX");
		glUniformMatrix4fv(rotXLocation, 1, GL_FALSE, &transformX[0][0]);
		int rotYLocation = glGetUniformLocation(shaderProgram, "rotY");
		glUniformMatrix4fv(rotYLocation, 1, GL_FALSE, &transformY[0][0]);
		int rotZLocation = glGetUniformLocation(shaderProgram, "rotZ");
		glUniformMatrix4fv(rotZLocation, 1, GL_FALSE, &transformZ[0][0]);
		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		for (std::vector<t_face>::iterator it = data.v_faces.begin(); it != data.v_faces.end(); it++)
			glDrawElements(GL_LINE_LOOP, (*it).size, GL_UNSIGNED_INT, (void *)((*it).offset * sizeof(GLuint)));
		glBindVertexArray(0);
		// END
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	terminate();
}
#include "test.hpp"
// c++ parsetest.cpp parse.cpp libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1
const GLint WIDTH = 800, HEIGHT = 600;
const float SPEED = 0.02;
void parse(char *filename, t_data *data);

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
	data->mov[0] = 0;
	data->mov[1] = 0;
	data->mov[2] = 0;
}

GLFWwindow *createWindow()
{
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "fine I'm changing the name", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (nullptr == window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
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
	key = glfwGetKey(window, GLFW_KEY_W);
	if (key == GLFW_PRESS) {
		data->mov[1] -= SPEED;
	}
	key = glfwGetKey(window, GLFW_KEY_S);
	if (key == GLFW_PRESS) {
		data->mov[1] += SPEED;
	}
	key = glfwGetKey(window, GLFW_KEY_A);
	if (key == GLFW_PRESS) {
		data->mov[0] += SPEED;
	}
	key = glfwGetKey(window, GLFW_KEY_D);
	if (key == GLFW_PRESS) {
		data->mov[0] -= SPEED;
	}
	key = glfwGetKey(window, GLFW_KEY_I);
	if (key == GLFW_PRESS) {
		data->mov[2] += SPEED;
	}
	key = glfwGetKey(window, GLFW_KEY_O);
	if (key == GLFW_PRESS) {
		data->mov[2] -= SPEED;
	}
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
	std::string path("./resources/42.obj");
	// char *path = "resources/teapot2.obj";
	init(&data);
	parse(path, &data);
	normalize_delete_this(&(data.v_vertices));
	GLFWwindow *window = createWindow();
	Shader shader("vertexshader.glsl", "fragmentshader.glsl");

	// TEMP BLOCK START
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	float transformX[4][4];
	float transformY[4][4];
	float transformZ[4][4];
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	// TEMP BLOCK END
	while (!glfwWindowShouldClose(window))
	{
		processInput(window, &data);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render
		// glUseProgram(shaderProgram);
		shader.use();
		// rotX(data.rot[0], transformX);
		// rotY(data.rot[1], transformY);
		// rotZ(data.rot[2], transformZ);
		// int rotXLocation = glGetUniformLocation(shader.getId(), "rotX");
		// glUniformMatrix4fv(rotXLocation, 1, GL_FALSE, &transformX[0][0]);
		// int rotYLocation = glGetUniformLocation(shader.getId(), "rotY");
		// glUniformMatrix4fv(rotYLocation, 1, GL_FALSE, &transformY[0][0]);
		// int rotZLocation = glGetUniformLocation(shader.getId(), "rotZ");
		// glUniformMatrix4fv(rotZLocation, 1, GL_FALSE, &transformZ[0][0]);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(data.rot[0]), glm::vec3(1.0f, 0.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(data.rot[1]), glm::vec3(0.0f, 1.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(data.rot[2]), glm::vec3(0.0f, 1.0f, 1.0f));
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(data.mov[0], data.mov[1], data.mov[2] - 3.0f)); 

		// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
		// int movLocation = glGetUniformLocation(shader.getId(), "mov");
		// glUniform3f(movLocation, data.mov[0], data.mov[1], data.mov[2]);
		int modelLocation = glGetUniformLocation(shader.getId(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
		int viewLocation = glGetUniformLocation(shader.getId(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		int projLocation = glGetUniformLocation(shader.getId(), "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);
		// update the uniform color
		int vertexColorLocation = glGetUniformLocation(shader.getId(), "ourColor");
		glBindVertexArray(VAO);
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
		for (std::vector<t_face>::iterator it = data.v_faces.begin(); it != data.v_faces.end(); it++)
			glDrawElements(GL_TRIANGLE_FAN, (*it).size, GL_UNSIGNED_INT, (void *)((*it).offset * sizeof(GLuint)));
		glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
		for (std::vector<t_face>::iterator it = data.v_faces.begin(); it != data.v_faces.end(); it++)
			glDrawElements(GL_LINE_LOOP, (*it).size, GL_UNSIGNED_INT, (void *)((*it).offset * sizeof(GLuint)));
		glBindVertexArray(0);
		// END
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	terminate();
}
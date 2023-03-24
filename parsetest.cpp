#include "test.hpp"
// c++ parsetest.cpp parse.cpp libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1
const GLint WIDTH = 800, HEIGHT = 600;
const float SPEED = 0.02;
void parse(char *filename, t_data *data);

void init(t_data *data)
{
	data->rot[0] = 0;
	data->rot[1] = 0;
	data->rot[2] = 0;
	data->mov[0] = 0;
	data->mov[1] = 0;
	data->mov[2] = 0;
	data->minX = 2e30;
	data->minY = 2e30;
	data->minZ = 2e30;
	data->maxX = -2e30;
	data->maxY = -2e30;
	data->maxZ = -2e30;
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

void normalize_delete_this(std::vector<float> *vertices)
{
	float max = *(std::max_element(vertices->begin(), vertices->end()));
	float min = *(std::min_element(vertices->begin(), vertices->end()));
	float factor = (min * -1 > max) ? 0.9 / min : 0.9 / max;
	for (std::vector<float>::iterator it = vertices->begin(); it != vertices->end(); it++)
		*it *= factor;
}

void another_temp(t_data *data) {
	float temp;
	temp = data->maxX - data->minX;
	temp = temp < 0 ? -temp : temp;
	data->mov[0] = temp/2 - data->maxX;
	temp = data->maxY - data->minY;
	temp = temp < 0 ? -temp : temp;
	data->mov[1] = temp/2 - data->maxY;
	temp = data->maxZ - data->minZ;
	temp = temp < 0 ? -temp : temp;
	data->mov[2] = temp/2 - data->maxZ;
	std::cout << data->maxX << " " << data->maxY << " " << data->maxZ << std::endl;
	std::cout << data->minX << " " << data->minY << " " << data->minZ << std::endl;
	std::cout << data->mov[0] << " " << data->mov[1] << " " << data->mov[2] << std::endl;
	for (std::vector<float>::iterator it = data->v_vertices.begin(); it != data->v_vertices.end(); it += 3) {
		*it += data->mov[0];
		*(it+1) += data->mov[1];
		*(it+2) += data->mov[2];
	}
	data->mov[0] = 0;
	data->mov[1] = 0;
	data->mov[2] = 0;
}

int main()
{
	t_data data;
	std::string path("./resources/teapot.obj");
	init(&data);
	parse(path, &data);
	another_temp(&data);
	normalize_delete_this(&(data.v_vertices));
	GLFW GLFW(WIDTH, HEIGHT, SPEED);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
	float col;
	int step = 2;
	glEnable(GL_DEPTH_TEST);
	// TEMP BLOCK END
	while (!GLFW.shouldClose())
	{
		// GLFW.processInput(&data);
		processInput(GLFW.getWindow(), &data);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render
		shader.use();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(data.rot[0]), glm::vec3(1.0f, 0.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(data.rot[1]), glm::vec3(0.0f, 1.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(data.rot[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(data.mov[0], data.mov[1], data.mov[2] - 3.0f)); 

		int modelLocation = glGetUniformLocation(shader.getId(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
		int viewLocation = glGetUniformLocation(shader.getId(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		int projLocation = glGetUniformLocation(shader.getId(), "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);
		// update the uniform color
		int vertexColorLocation = glGetUniformLocation(shader.getId(), "ourColor");
		glBindVertexArray(VAO);
		for (size_t i = 0; i < data.v_faces.size(); i++) {
			col = (float)(i%step) / step;
			glUniform4f(vertexColorLocation, col, col, col, 1.0f);
			glDrawElements(GL_TRIANGLE_FAN, data.v_faces[i].size, GL_UNSIGNED_INT, (void *)(data.v_faces[i].offset * sizeof(GLuint)));
		}
		glBindVertexArray(0);
		// END
		glfwPollEvents();
		glfwSwapBuffers(GLFW.getWindow());
	}
}
#include "test.hpp"
// c++ parsetest.cpp parse.cpp libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.02;
void parse(char *filename, t_data *data);

void init(t_data *data)
{
	data->rot = glm::mat4(1.0f);
	data->mov[0] = 0;
	data->mov[1] = 0;
	data->mov[2] = 0;
}

glm::mat4 rotObj(glm::mat4 mat, float angle, int mode)
{
    // mode 0 for X, 1 for Y, 2 for Z
    glm::vec3 axis;
    axis[mode] = 1.0f;
    mat = glm::rotate(mat, glm::radians(angle), axis);
    return mat;
}

void processInput(GLFWwindow *window, t_data *data)
{
	int key;
	key = glfwGetKey(window, GLFW_KEY_ESCAPE);
	if (key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	key = glfwGetKey(window, GLFW_KEY_UP);
	if (key == GLFW_PRESS)
		data->rot = rotObj(data->rot, -2.0, 0);
	key = glfwGetKey(window, GLFW_KEY_DOWN);
	if (key == GLFW_PRESS)
		data->rot = rotObj(data->rot, 2.0, 0);
	key = glfwGetKey(window, GLFW_KEY_LEFT);
	if (key == GLFW_PRESS)
		data->rot = rotObj(data->rot, 2.0, 1);
	key = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (key == GLFW_PRESS)
		data->rot = rotObj(data->rot, -2.0, 1);
	key = glfwGetKey(window, GLFW_KEY_R);
	if (key == GLFW_PRESS)
		data->rot = rotObj(data->rot, 2.0, 2);
	key = glfwGetKey(window, GLFW_KEY_T);
	if (key == GLFW_PRESS)
		data->rot = rotObj(data->rot, -2.0, 2);
	key = glfwGetKey(window, GLFW_KEY_W);
	if (key == GLFW_PRESS)
		data->mov[1] -= MOV_SPEED;
	key = glfwGetKey(window, GLFW_KEY_S);
	if (key == GLFW_PRESS)
		data->mov[1] += MOV_SPEED;
	key = glfwGetKey(window, GLFW_KEY_A);
	if (key == GLFW_PRESS)
		data->mov[0] += MOV_SPEED;
	key = glfwGetKey(window, GLFW_KEY_D);
	if (key == GLFW_PRESS)
		data->mov[0] -= MOV_SPEED;
	key = glfwGetKey(window, GLFW_KEY_I);
	if (key == GLFW_PRESS)
		data->mov[2] += MOV_SPEED;
	key = glfwGetKey(window, GLFW_KEY_O);
	if (key == GLFW_PRESS)
		data->mov[2] -= MOV_SPEED;
}

void normalize_delete_this(std::vector<float> *vertices)
{
	float max = *(std::max_element(vertices->begin(), vertices->end()));
	float min = *(std::min_element(vertices->begin(), vertices->end()));
	float factor = (min * -1 > max) ? 0.9 / min : 0.9 / max;
	for (std::vector<float>::iterator it = vertices->begin(); it != vertices->end(); it++)
		*it *= factor;
}

void center_obj(t_data *data)
{
	float center[3];
	int size = data->v_vertices.size();
	for (int i = 0; i < 3; i++)
		center[i] = 0;
	for (int i = 0; i < size; i += 3)
	{
		center[0] += data->v_vertices[i];
		center[1] += data->v_vertices[i + 1];
		center[2] += data->v_vertices[i + 2];
	}
	center[0] /= size / 3;
	center[1] /= size / 3;
	center[2] /= size / 3;
	for (int i = 0; i < size; i += 3)
	{
		data->v_vertices[i] -= center[0];
		data->v_vertices[i + 1] -= center[1];
		data->v_vertices[i + 2] -= center[2];
	}
}


int main()
{
	t_data data;
	std::string path("./resources/teapot.obj");
	init(&data);
	parse(path, &data);
	center_obj(&data);
	normalize_delete_this(&(data.v_vertices));
	GLFW GLFW(WIDTH, HEIGHT, MOV_SPEED);
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
	glm::mat4 view;
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	float col;
	int step = 2;
	glEnable(GL_DEPTH_TEST);
	// TEMP BLOCK END
	glm::vec3 temp;
	while (!GLFW.shouldClose())
	{
		// GLFW.processInput(&data);
		processInput(GLFW.getWindow(), &data);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render
		shader.use();
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(data.mov[0], data.mov[1], data.mov[2] - 2.0f));

		int modelLocation = glGetUniformLocation(shader.getId(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &data.rot[0][0]);
		int viewLocation = glGetUniformLocation(shader.getId(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		int projLocation = glGetUniformLocation(shader.getId(), "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);
		// update the uniform color
		int vertexColorLocation = glGetUniformLocation(shader.getId(), "ourColor");
		glBindVertexArray(VAO);
		for (size_t i = 0; i < data.v_faces.size(); i++)
		{
			col = (float)(i % step) / step;
			glUniform4f(vertexColorLocation, col, col, col, 1.0f);
			glDrawElements(GL_TRIANGLE_FAN, data.v_faces[i].size, GL_UNSIGNED_INT, (void *)(data.v_faces[i].offset * sizeof(GLuint)));
		}
		glBindVertexArray(0);
		// END
		glfwPollEvents();
		glfwSwapBuffers(GLFW.getWindow());
	}
}
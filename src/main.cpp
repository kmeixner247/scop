#include "../include/scop.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"
// c++ parsetest.cpp parse.cpp libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1
const GLint WIDTH = 800, HEIGHT = 600;
const float MOV_SPEED = 0.05;
void parse(char *filename, t_data *data);

void scaleObj(std::vector<t_vbo_element> *vbo) {
	float max = (*vbo)[0].vertex[0];
	float min = (*vbo)[0].vertex[0];
	for (int i = 0; i < vbo->size(); i++) {
		for (int j = 0; j < 3; j++) {
			if ((*vbo)[i].vertex[j] > max)
				max = (*vbo)[i].vertex[j];
			if ((*vbo)[i].vertex[j] < min)
				min = (*vbo)[i].vertex[j];
		}
	}
	float factor = (min * -1 > max) ? 1.0 / min : 1.0 / max;
	for (int i = 0; i < vbo->size(); i++)
		(*vbo)[i].vertex *= factor;
}


void centerObj(t_data *data)
{
	ft::vec3 center;
	int size = data->vbo.size();
	for (int i = 0; i < 3; i++)
		center[i] = 0;	
	for (int i = 0; i < size; i ++)
		center += data->vbo[i].vertex;
	center /= size;
	for (int i = 0; i < size; i++)
		data->vbo[i].vertex -= center;
}

void sphericalmap(t_data *data) {
	ft::vec2 v;
	for (std::vector<t_vbo_element>::iterator it = data->vbo.begin(); it != data->vbo.end(); it++) {
		v.x = atan2((*it).vertex.x, (*it).vertex.z) / (2 * M_PI) + 0.5;
		v.y = asin((*it).vertex.y) / M_PI + 0.5;
		v *= 1;
		(*it).texcoords = v;
	}
}

void cubemap(t_data *data) {
	ft::vec2 v;
	float minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
	for (std::vector<t_vbo_element>::iterator it = data->vbo.begin(); it != data->vbo.end(); it++) {
		if ((*it).vertex.x > maxx)
			maxx = (*it).vertex.x;
		if ((*it).vertex.x < minx)
			minx = (*it).vertex.x;
		if ((*it).vertex.y > maxy)
			maxy = (*it).vertex.y;
		if ((*it).vertex.y < miny)
			miny = (*it).vertex.y;
		if ((*it).vertex.z > maxz)
			maxz = (*it).vertex.z;
		if ((*it).vertex.z < minz)
			minz = (*it).vertex.z;
	}
	std::cout << maxx << ", " << minx << ", " << maxy << ", " << miny << ", " << maxz << ", " << minz << ", " << std::endl;
	float absx, absy, absz;
	float distminx, distmaxx, distminy, distmaxy, distminz, distmaxz, min;
	int i = 0;
	for (std::vector<t_vbo_element>::iterator it = data->vbo.begin(); it != data->vbo.end(); it++) {
		distminx = abs((*it).vertex.x - minx);
		distmaxx = abs((*it).vertex.x - maxx);
		distminy = abs((*it).vertex.y - miny);
		distmaxy = abs((*it).vertex.y - maxy);
		distminz = abs((*it).vertex.z - minz);
		distmaxz = abs((*it).vertex.z - maxz);
		min = std::min(distminx, std::min(distmaxx, std::min(distminy, std::min(distmaxy, std::min(distminz, distmaxz)))));
		if (min == distminx || min == distmaxx) {
			v.x = (*it).vertex.y;
			v.y = (*it).vertex.z;
		}
		else if (min == distminy || min == distmaxy) {
			v.x = (*it).vertex.x;
			v.y = (*it).vertex.z;
		}
		else {
			v.x = (*it).vertex.x;
			v.y = (*it).vertex.y;
		}
		it->texcoords = v;
	}
}

// void calc_normals(t_data *data) {
// 	int index;
// 	int prev;
// 	for (int i = 0; i < data->v_faces.size(); i++) {
// 		prev = data->v_indices[data->v_faces[i].offset];
// 		for (int j = 1; j < data->v_faces[i].size; j++) {
// 			index = data->v_indices[data->v_faces[i].offset + j];
// 			std::cout << crossproduct(data->vbo[prev].vertex, data->vbo[index].vertex) << std::endl;
// 			prev = index;
// 		}
// 		std::cout << std::endl;
// 	}
// }

int main()
{
	t_data data;
	std::string path("resources/skull2.obj");
	parse(path, data);
	centerObj(&data);
	scaleObj(&(data.vbo));
	// calc_normals(&data);
	// cubemap(&data);
	// sphericalmap(&data);
	GLFW GLFW(WIDTH, HEIGHT, MOV_SPEED);
	Shader shader("vertexshader.glsl", "fragmentshader.glsl");

	// TEMP BLOCK START
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, data.v_vertices.size() * 3 * sizeof(float), &(data.v_vertices[0]), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, data.vbo.size() * 8 * sizeof(float), &(data.vbo[0]), GL_STATIC_DRAW);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.v_indices.size() * sizeof(int), &(data.v_indices[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	ft::mat4 view;
	ft::mat4 proj = ft::perspective(ft::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	float col;
	int step = 2;
	glEnable(GL_DEPTH_TEST);
	// TEMP BLOCK END
	// TEXTURE BLOCK START
	int twidth, theight, nrChannels;
	unsigned char *tdata = stbi_load("resources/wall.jpg", &twidth, &theight, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(tdata);
	// TEXTURE BLOCK END
	// data.ambient = ft::vec3(0.0f, 0.0f, 0.0f);
	data.ambient = ft::vec3(0.4f, 0.4f, 0.4f);
	// data.diffuse = ft::vec3(0.0f ,0.0f, 0.0f);
	data.diffuse = ft::vec3(0.4f ,0.0f, 0.0f);
	// data.specular = ft::vec3(0.0f ,0.0f, 0.0f);
	data.specular = ft::vec3(0.3f ,0.3f, 0.3f);
	while (!GLFW.shouldClose())
	{
		GLFW.processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render
		shader.use();
		view = ft::mat4(1.0f);
		ft::vec3 asdf(GLFW.getMov(0), GLFW.getMov(1), GLFW.getMov(2) - 2.0f);
		// view = ft::translate(view, ft::vec3(GLFW.getMov(0), GLFW.getMov(1), GLFW.getMov(2) - 2.0f));
		view = ft::translate(view, asdf);
		int lightPosLocation = glGetUniformLocation(shader.getId(), "lightPos");
		glUniform3f(lightPosLocation, 1.0f, 0, 0.5f);
		int viewPosLocation = glGetUniformLocation(shader.getId(), "viewPos");
		// glUniform3f(viewPosLocation, 0.0f, 0.0f, -2.0f);
		glUniform3f(viewPosLocation, asdf.x, asdf.y, asdf.z);
		int ambientLocation = glGetUniformLocation(shader.getId(), "ambientColor");
		glUniform3f(ambientLocation, data.ambient.x, data.ambient.y, data.ambient.z);
		int diffuseLocation = glGetUniformLocation(shader.getId(), "diffuseColor");
		glUniform3f(diffuseLocation, data.diffuse.x, data.diffuse.y, data.diffuse.z);
		int specularLocation = glGetUniformLocation(shader.getId(), "specularColor");
		glUniform3f(specularLocation, data.specular.x, data.specular.y, data.specular.z);
		int modelLocation = glGetUniformLocation(shader.getId(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, GLFW.getRot());
		int viewLocation = glGetUniformLocation(shader.getId(), "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		int projLocation = glGetUniformLocation(shader.getId(), "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);

		glBindVertexArray(VAO);
		for (size_t i = 0; i < data.v_faces.size(); i++)
		{
			// col = (float)(i % step) / step;
			// glUniform4f(vertexColorLocation, col, col, col, 1.0f);
			glBindTexture(GL_TEXTURE_2D, texture);
			glDrawElements(GL_TRIANGLE_FAN, data.v_faces[i].size, GL_UNSIGNED_INT, (void *)(data.v_faces[i].offset * sizeof(GLuint)));
		}
		glBindVertexArray(0);
		// END
		glfwPollEvents();
		glfwSwapBuffers(GLFW.getWindow());
	}
}

#ifndef TEST_HPP
#define TEST_HPP
#include <OpenGL/gl3.h>
#include "include/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
typedef struct s_face
{
	int offset;
	int size;
} t_face;

typedef struct s_data
{
	std::vector<float> v_vertices;
	std::vector<int> v_indices;
	std::vector<t_face> v_faces;
	float rot[3];
	std::string fragmentShaderSource;
	std::string vertexShaderSource;
} t_data;

void parse(std::string filename, t_data *data);
#endif
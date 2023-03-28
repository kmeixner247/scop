#ifndef SCOP_HPP
#define SCOP_HPP
#include <OpenGL/gl3.h>
#include "include/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "Shader.hpp"
#include "GLFW.hpp"
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
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
} t_data;

void parse(std::string filename, t_data *data);
#endif
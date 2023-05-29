#pragma once

#include <OpenGL/gl3.h>
#include "../external/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "objects/Shader.hpp"
#include "math/math.hpp"
#include "objects/GLFW.hpp"

typedef struct s_face
{
	int offset;
	int size;
	std::vector<ft::vec3> vertices;
	std::vector<ft::vec2> texcoords;
	ft::vec3 normal;
	std::vector<std::string> raw;
} t_face;

typedef struct s_vbo_element
{
	ft::vec3 vertex;
	ft::vec2 texcoords;
	ft::vec3 normal;
} t_vbo_element;

typedef struct s_data
{
	std::vector<ft::vec3> v_vertices;
	std::vector<ft::vec2> v_texcoords;
	std::vector<ft::vec3> v_normals;
	std::vector<int> v_indices;
	std::vector<t_face> v_faces;
	std::vector<t_vbo_element> vbo;
	ft::vec3 ambient;
	ft::vec3 diffuse;
	ft::vec3 specular;
} t_data;

void parse(const std::string &filename, t_data &data);
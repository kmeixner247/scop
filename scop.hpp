#ifndef SCOP_HPP
#define SCOP_HPP
#include <OpenGL/gl3.h>
#include "include/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include "Shader.hpp"
#include "math.hpp"
#include "GLFW.hpp"

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
	ft::vec3 normal;
	ft::vec2 texcoords;
} t_vbo_element;

typedef struct s_data
{
	std::vector<ft::vec3> v_vertices;
	std::vector<ft::vec2> v_texcoords;
	std::vector<ft::vec2> v_normals;
	std::vector<int> v_indices;
	std::vector<t_face> v_faces;
	std::vector<t_vbo_element> vbo;
} t_data;

void parse(std::string filename, t_data *data);
#endif
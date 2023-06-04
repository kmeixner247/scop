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

typedef struct s_vbo_element {
    ft::vec3 vertex;
    ft::vec2 texCoords;
    ft::vec3 normal;
} t_vbo_element;

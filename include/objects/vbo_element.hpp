#pragma once

#include "../math/math.hpp"

typedef struct s_vbo_element {
    ft::vec3 vertex;
    ft::vec2 texCoords;
    ft::vec3 normal;
    ft::vec3 randomColor;
} t_vbo_element;

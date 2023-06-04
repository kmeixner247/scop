#pragma once
#include <OpenGL/gl3.h>
#include <vector>
#include "../scop.hpp"

class VertexBuffer {
private:
    unsigned int _id;

public:
    VertexBuffer();
    VertexBuffer(VertexBuffer const &rhs);
    VertexBuffer &operator=(VertexBuffer const &rhs);
    ~VertexBuffer();
    void init();
    void bind();
    void push(std::vector<t_vbo_element> const &data);
    unsigned int getId() const;
};

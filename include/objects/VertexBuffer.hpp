#pragma once
#include <OpenGL/gl3.h>
#include <vector>
#include "../scop.hpp"

class VertexBuffer {
private:
    unsigned int _id;

public:
    VertexBuffer() { 
        glGenBuffers(1, &_id);
    }
    VertexBuffer(VertexBuffer const &rhs) { _id = rhs._id; }
    VertexBuffer &operator=(VertexBuffer const &rhs) { _id = rhs._id; return *this; }
    ~VertexBuffer() {}
    void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }
    void push(std::vector<t_vbo_element> const &data) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, data.size() * 8 * sizeof(float), &(data[0]), GL_STATIC_DRAW);
    }
    unsigned int getId() const {
        return _id;
    }
};
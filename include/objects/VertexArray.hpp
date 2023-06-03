#pragma once

#include "VertexBuffer.hpp"
#include <OpenGL/gl3.h>

class VertexArray {
private:
    unsigned int _id;
public:
    void configure();
    VertexArray();
    VertexArray(VertexArray const &rhs);
    VertexArray &operator=(VertexArray const &rhs);
    ~VertexArray();
    void bind();
    unsigned int getId() const;
};

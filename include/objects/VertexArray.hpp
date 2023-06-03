#pragma once

#include "VertexBuffer.hpp"

class VertexArray {
private:
    int _id;
public:
    VertexArray();
    VertexArray(VertexArray const &rhs);
    VertexArray &operator=(VertexArray);
    ~VertexArray();
    void bind();
}
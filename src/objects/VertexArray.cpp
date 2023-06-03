#include "../../include/objects/VertexArray.hpp"

VertexArray::VertexArray() {
    glGenBuffers(1, &_id);
}

VertexArray::VertexArray(VertexArray const &rhs) {
    _id = rhs.id;
}

VertexArray::VertexArray(VertexBuffer const &vbo) {
    glGenBuffers(1, &_id);
    bind()
}

VertexArray &VertexArray::operator=(VertexArray) {
    _id = rhs.id;
}

VertexArray::~VertexArray() {}

void VertexArray::bind() {
    glBindVertexArray(_id);
}
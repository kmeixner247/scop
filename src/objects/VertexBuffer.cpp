#include "../../include/objects/VertexBuffer.hpp"

VertexBuffer::VertexBuffer() : _id(0) { 
}

VertexBuffer::VertexBuffer(VertexBuffer const &rhs) {
    _id = rhs._id;
}

VertexBuffer &VertexBuffer::operator=(VertexBuffer const &rhs) {
    _id = rhs._id; return *this;
}

VertexBuffer::~VertexBuffer() {
}

void VertexBuffer::init() {
    glGenBuffers(1, &_id);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::push(std::vector<t_vbo_element> const &data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * 8 * sizeof(float), &(data[0]), GL_STATIC_DRAW);
}

unsigned int VertexBuffer::getId() const {
    return _id;
}

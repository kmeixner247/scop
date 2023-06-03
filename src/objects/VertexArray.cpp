#include "../../include/objects/VertexArray.hpp"

void VertexArray::configure() {
    bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &_id);
}

VertexArray::VertexArray(VertexArray const &rhs) {
    _id = rhs._id;
}

VertexArray &VertexArray::operator=(VertexArray const &rhs) {
    _id = rhs._id;
    return *this;
}

VertexArray::~VertexArray() {}

void VertexArray::bind() {
    glBindVertexArray(_id);
}

unsigned int VertexArray::getId() const {
    return _id;
}
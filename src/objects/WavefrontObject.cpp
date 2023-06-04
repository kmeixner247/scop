#include "../../include/objects/WavefrontObject.hpp"

WavefrontObject::WavefrontObject() {
}

WavefrontObject::WavefrontObject(WavefrontObject const &rhs) : _data(rhs._data), _vao(rhs._vao), _vbo(rhs._vbo) {
}

WavefrontObject &WavefrontObject::operator=(WavefrontObject const &rhs) {
    _data = rhs._data;
    _vao = rhs._vao;
    _vbo = rhs._vbo;
    return *this;
};

WavefrontObject::~WavefrontObject() {
}

void WavefrontObject::draw() {
    _vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, size());
}

void WavefrontObject::push() {
    _vbo.init();
    _vbo.push(_data);
    _vao.init();
    _vao.configure();
}

void WavefrontObject::add(t_vbo_element const &face) {
    _data.push_back(face);
}

int WavefrontObject::size() {
    return _data.size();
}

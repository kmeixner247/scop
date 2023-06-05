#include "../../include/objects/WavefrontObject.hpp"

WavefrontObject::WavefrontObject() {
}

WavefrontObject::WavefrontObject(WavefrontObject const &rhs) : _data(rhs._data), _vao(rhs._vao), _vbo(rhs._vbo), _model(rhs._model) {
}

WavefrontObject &WavefrontObject::operator=(WavefrontObject const &rhs) {
    _data = rhs._data;
    _vao = rhs._vao;
    _vbo = rhs._vbo;
    _model = rhs._model;
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

void WavefrontObject::scale(float const &factor) {
    ft::vec3 scaler(factor, factor, factor);
    this->_model = ft::scale(this->_model, scaler);
}

void WavefrontObject::move(ft::vec3 &vec) {
    for (auto it = _data.begin(); it != _data.end(); it++) {
        it->vertex += vec;
    }
}

void WavefrontObject::translate(ft::vec3 &vec) {
    this->_model = ft::translate(this->_model, vec);
}

std::vector<t_vbo_element> WavefrontObject::getData() const {
    return _data;
}

void WavefrontObject::rotate(float angle, int mode) {
    // mode 0 for X, 1 for Y, 2 for Z
    ft::vec3 axis;
    axis[mode] = 1.0f;
    this->_model = ft::rotate(this->_model, ft::radians(angle), axis);
}

ft::mat4 WavefrontObject::getModel() const {
    return _model;
}

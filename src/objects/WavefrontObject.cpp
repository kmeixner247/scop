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
    scale(2.0);
    scale(2.0);
    center();
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

void WavefrontObject::center() {
    ft::vec3 center;
    for (auto obj : _data) {
        center.x += obj.vertex.x;
        center.y += obj.vertex.y;
        center.z += obj.vertex.z;
    }
    center /= float(_data.size());
    for (auto it = _data.begin(); it != _data.end(); it++) {
        it->vertex -= center;
    }
}

void WavefrontObject::scale(float const &scale) {
    float max = 0;
    for (auto obj : _data) {
        if (fabs(obj.vertex.x) > max)
            max = obj.vertex.x;
        if (fabs(obj.vertex.y) > max)
            max = obj.vertex.y;
        if (fabs(obj.vertex.z) > max)
            max = obj.vertex.z;
    }
    for (auto it = _data.begin(); it != _data.end(); it++) {
        it->vertex = it->vertex / max * scale/2;
    }
    std::cout << max << std::endl;
    // for (auto obj: _data) {
    //     std::cout << obj.vertex << std::endl;
    // }
}
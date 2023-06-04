#include "../../include/objects/Camera.hpp"

Camera::Camera() : _pos(ft::vec3(0, 0, 3)), _dir(ft::vec3(0, 0, -1)) {
}

Camera::Camera(Camera const &rhs) : _pos(rhs._pos), _dir(rhs._dir) {
}

Camera &Camera::operator=(Camera const &rhs) {
    _pos = rhs._pos; _dir = rhs._dir;
    return *this;
}

Camera::~Camera() {
}

void Camera::setPos(ft::vec3 const &pos) { 
    _pos = pos;
}

ft::vec3 Camera::getPos() const {
    return _pos;
}

void Camera::setDir(ft::vec3 const &dir) {
    _dir = dir;
}

ft::vec3 Camera::getDir() const {
    return _dir;
}

void Camera::move(ft::vec3 const &vec) {
    _pos += vec;
}

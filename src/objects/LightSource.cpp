#include "../../include/objects/LightSource.hpp"

LightSource::LightSource() : _pos(ft::vec3()) {
}

LightSource::LightSource(LightSource const &rhs) : _pos(rhs._pos) {
}

LightSource &LightSource::operator=(LightSource const &rhs) {
    _pos = rhs._pos;
    return *this;
}

LightSource::~LightSource() {
}

void LightSource::setPos(ft::vec3 const &pos) {
    _pos = pos;
}

ft::vec3 LightSource::getPos() const {
    return _pos;
}

#include "../../include/objects/Scene.hpp"

Scene::Scene() {
}

Scene::Scene(Scene const &rhs) {
}

Scene &Scene::operator=(Scene const &rhs) {
    return *this;
}

Scene::~Scene() {
}

void Scene::setLightPos(ft::vec3 const &pos) {
    _lightSource.setPos(pos);
}

ft::vec3 Scene::getLightPos() const {
    return _lightSource.getPos();
}

void Scene::setCameraPos(ft::vec3 const &pos) {
    _camera.setPos(pos);
}

ft::vec3 Scene::getCameraPos() const {
    return _camera.getPos();
}

void Scene::moveCamera(ft::vec3 const &vec) { 
    _camera.move(vec); 
}

void Scene::loadObjects(WavefrontLoader &loader) {
    _objects = loader._objects;
}

void Scene::loadMtllib(WavefrontLoader &loader) {
    _v_mtllib = loader._v_mtllib;
}

void Scene::bind() {
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        it->second.push();
    }
}

void Scene::center() {
    ft::vec3 center;
    int size = 0;
    for (auto obj : _objects) {
        size += obj.second.size();
        for (auto face : obj.second.getData()) {
            center += face.vertex;
        }
    }
    center /= size;
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        it->second.move(-center);
    }
}

void Scene::scale(float const &scale) {
    float max = 0;
    for (auto obj : _objects) {
        for (auto face : obj.second.getData()) {
        if (fabs(face.vertex.x) > max)
            max = face.vertex.x;
        if (fabs(face.vertex.y) > max)
            max = face.vertex.y;
        if (fabs(face.vertex.z) > max)
            max = face.vertex.z;
        }
    }
    float factor = (scale / 2) / max;
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        it->second.scale(factor);
    }
}

void Scene::draw(Shader const &shader) const {
    shader.use();
    for (auto test1 : _objects) {
        for (auto it = _v_mtllib.begin(); it != _v_mtllib.end(); it++) {
            if (!it->getName().compare(test1.first)) {
                shader.useMaterial(*it);
            }
        }
        test1.second.draw();
    }
    glBindVertexArray(0);
}

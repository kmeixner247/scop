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

ft::vec3 Scene::getLightPos(ft::vec3 const &pos) const {
    return _lightSource.getPos();
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





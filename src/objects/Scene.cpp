#include "../../include/objects/Scene.hpp"

void Scene::_updateRatio() {
    if (_ratio >= 1) {
        _ratio = 1.0f;
    }
    if (_ratio <= 0) {
        _ratio = 0.0f;
    }
    _ratio += _ratioChange;
}

Scene::Scene() {
}

Scene::Scene(Scene const &rhs) {
}

Scene &Scene::operator=(Scene const &rhs) {
    return *this;
}

Scene::~Scene() {
}

void Scene::init(GLint const &width, GLint const &height) {
    glEnable(GL_DEPTH_TEST);
    _view = ft::translate(ft::mat4(1.0f), ft::vec3(0,0,-3));
	_proj = ft::perspective(ft::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    _ratio = 0.0f;
    _ratioChange = 0.0f;
}

void Scene::setLightPos(ft::vec3 const &pos) {
    _lightSource.setPos(pos);
}

ft::vec3 Scene::getLightPos() const {
    return _lightSource.getPos();
}

void Scene::moveCamera(ft::vec3 const &vec) { 
    _view = ft::translate(_view, -vec);
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
        it->second.translate(center);
    }
}

void Scene::scale(float const &factor){
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        it->second.scale(factor);
    }
}

void Scene::scaleTo(float const &scale) {
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

void Scene::draw(Shader const &shader) {
    shader.use();
    shader.useValue("projMtx", _proj);
    shader.useValue("viewMtx", _view);
    shader.useValue("lightPos", _lightSource.getPos());
    _updateRatio();
    shader.useValue("textureRandomRatio", _ratio);
    for (auto test1 : _objects) {
        for (auto it = _v_mtllib.begin(); it != _v_mtllib.end(); it++) {
            if (!it->getName().compare(test1.first)) {
                shader.useMaterial(*it);
            }
        }
        shader.useValue("modelMtx", test1.second.getModel());
        test1.second.draw();
    }
    glBindVertexArray(0);
}

void Scene::rotateObjects(float angle, int mode) {
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        it->second.rotate(angle, mode);
    }
}

void Scene::transitionTexture() {
    if (_ratio <= 0.0f)
        _ratioChange = 0.03f;
    else if (_ratio >= 1.0f)
        _ratioChange = -0.03f;
}

#pragma once

#include <vector>
#include "../math/vec3.hpp"
#include "../math/vec2.hpp"
#include "Material.hpp"
#include "VertexArray.hpp"
#include "fstream"
#include "WavefrontLoader.hpp"

#include <OpenGL/gl3.h>

class LightSource {
private:
    ft::vec3 _pos;
public:
    LightSource() : _pos(ft::vec3()) {}
    LightSource(LightSource const &rhs) : _pos(rhs._pos) {}
    LightSource &operator=(LightSource const &rhs) { _pos = rhs._pos; return *this; }
    ~LightSource() {}
    void setPos(ft::vec3 const &pos) {
        _pos = pos;
    }
    ft::vec3 getPos() const {
        return _pos;
    }
};

class Camera {
private:
    ft::vec3 _pos;
    ft::vec3 _dir;
public:
    Camera() : _pos(ft::vec3(0, 0, -3)), _dir(ft::vec3(0, 0, 1)) {}
    Camera(Camera const &rhs) : _pos(rhs._pos), _dir(rhs._dir) {}
    Camera &operator=(Camera const &rhs) { _pos = rhs._pos; _dir = rhs._dir; return *this;}
    ~Camera() {}
    void setPos(ft::vec3 const &pos) { _pos = pos; }
    ft::vec3 getPos() const { return _pos; }
    void setDir(ft::vec3 const &dir) { _dir = dir; }
    ft::vec3 getDir() const { return _dir; }
    void move(ft::vec3 const &vec) { _pos += vec; }
    //TODO: Rotate function
};

class Scene {
private:
    typedef struct s_vbo_element {
        ft::vec3 vertex;
        ft::vec2 texCoords;
        ft::vec3 normal;
    } t_vbo_element;

    typedef void(Scene::*handlerFunction)(std::string_view);
    std::map<std::string, handlerFunction> _lineHandlerMap;
    std::string _src;

    // lightsource
    LightSource _lightSource;
public:
    void setLightPos(ft::vec3 const &pos) {
        _lightSource.setPos(pos);
    }

    ft::vec3 getLightPos(ft::vec3 const &pos) const {
        return _lightSource.getPos();
    }


private:
    // camera
    Camera _camera;

public:
    void moveCamera(ft::vec3 const &vec) { 
        _camera.move(vec); 
    }


private:
    std::map<std::string, WavefrontObject> _objects;
public:
    void loadObjects(WavefrontLoader &loader) {
        _objects = loader._objects;
    }
private:
    // all the different materials, might have to activate different ones
    std::vector<Material> _v_mtllib;
public:
    void loadMtllib(WavefrontLoader &loader) {
        _v_mtllib = loader._v_mtllib;
    }

    Scene() {}
    Scene(Scene const &rhs) {}
    Scene &operator=(Scene const &rhs) { return *this; }

    
public:
    Scene(std::string const &path);

    void bind() {
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
            it->second.push();
        }
    }

    void draw() {
        for (auto test1 : _objects) {
            test1.second.draw();
        }
		glBindVertexArray(0);
    }

    ~Scene() {};
};
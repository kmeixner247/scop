#pragma once

#include <vector>
#include "../math/vec3.hpp"
#include "../math/vec2.hpp"
#include "Material.hpp"
#include "fstream"


#include <OpenGL/gl3.h>

class WavefrontLoader {

};

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
    // basically temps
    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec2> _v_texcoords;
    std::vector<ft::vec3> _v_normals;

    // all the different materials, might have to activate different ones
    std::vector<Material> _v_mtllib;

    // the important data segment. Will need different ones for different groups/objects?
    std::vector<t_vbo_element> _vbo;

    std::vector<Material> _parseMaterials(std::string const &src);
    void _readFileIntoString(std::string const &path);
    void _interpretLine(std::string_view const &lineView);
    void _initializeLineHandlerMap();
    void _handleMtllib(std::string_view lineView);
    void _handleVertex(std::string_view lineView);
    void _handleTextureCoordinate(std::string_view lineView);
    void _handleNormalVector(std::string_view lineView);
    void _handleObject(std::string_view lineView);
    void _handleGroup(std::string_view lineView);
    void _handleMaterial(std::string_view lineView);
    void _handleFace(std::string_view lineView);
    void _handleSmoothShading(std::string_view lineView);
    Scene() {}
    Scene(Scene const &rhs) {}
    Scene &operator=(Scene const &rhs) { return *this; }
public:
    void draw();
    Scene(std::string const &path);
    void bind() {
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, _vbo.size() * 8 * sizeof(float), &(_vbo[0]), GL_STATIC_DRAW);
    }

    void draw(int VAO) {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, _vbo.size());
		glBindVertexArray(0);
    }

    ~Scene() {};
};
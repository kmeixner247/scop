#pragma once

#include "../math/math.hpp"
#include "WavefrontLoader.hpp"
#include "Camera.hpp"
#include "LightSource.hpp"
#include "Shader.hpp"
#include <OpenGL/gl3.h>
#include <vector>

class Scene {
private:
    LightSource _lightSource;
    Camera _camera;
    std::map<std::string, WavefrontObject> _objects;
    std::vector<Material> _v_mtllib;
public:
    Scene();
    Scene(Scene const &rhs);
    Scene &operator=(Scene const &rhs);
    ~Scene();
    
    void setLightPos(ft::vec3 const &pos);
    ft::vec3 getLightPos() const;
    void setCameraPos(ft::vec3 const &pos);
    ft::vec3 getCameraPos() const;
    void moveCamera(ft::vec3 const &vec);
    void loadObjects(WavefrontLoader &loader);
    void loadMtllib(WavefrontLoader &loader);
    void bind();
    void center();
    void scale(float const &factor);
    void scaleTo(float const &scale);
    void draw(Shader const &shader) const;
    void rotateObjects(float angle, int mode);
};

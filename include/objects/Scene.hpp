#pragma once

#include <vector>
#include "../math/vec3.hpp"
#include "../math/vec2.hpp"
#include "Material.hpp"
#include "VertexArray.hpp"
#include "fstream"
#include "WavefrontLoader.hpp"
#include "Camera.hpp"
#include "LightSource.hpp"
#include <OpenGL/gl3.h>


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
    ft::vec3 getLightPos(ft::vec3 const &pos) const;
    void moveCamera(ft::vec3 const &vec);
    void loadObjects(WavefrontLoader &loader);
    void loadMtllib(WavefrontLoader &loader);

    void bind();
    void draw();
};

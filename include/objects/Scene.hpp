#pragma once

#include "../math/math.hpp"

#include "WavefrontLoader.hpp"
#include "LightSource.hpp"
#include "Shader.hpp"
#include <OpenGL/gl3.h>
#include <vector>

class Scene {
private:
    LightSource _lightSource;
    ft::mat4 _proj;
    ft::mat4 _view;
    std::map<std::string, WavefrontObject> _objects;
    std::vector<Material> _v_mtllib;
    std::vector<Shader> _v_shaders;
    int _activeShader;
    float _ratio;
	float _ratioChange;
    void _updateRatio();
    Scene(Scene const &rhs);
    Scene &operator=(Scene const &rhs);
public:
    Scene();
    ~Scene();

    void init(GLint const &width, GLint const &height);
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
    void draw();
    void rotateObjects(float angle, int mode);
    void transitionTexture();
    void addShader(Shader &shader);
    void switchShader(int const &shaderIndex);
};

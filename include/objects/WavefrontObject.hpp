#pragma once
#include <vector>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class WavefrontObject {
private:   
    std::vector<t_vbo_element> _data;
    VertexArray _vao;
    VertexBuffer _vbo;
    ft::mat4 _model;
public:
    WavefrontObject();
    WavefrontObject(WavefrontObject const &rhs);
    WavefrontObject &operator=(WavefrontObject const &rhs);
    ~WavefrontObject();
    void draw();
    void push();
    void add(t_vbo_element const &face);
    int size();
    void scale(float const &factor);
    void move(ft::vec3 &vec);
    void translate(ft::vec3 &vec);
    void rotate(float angle, int mode);
    std::vector<t_vbo_element> getData() const;
    ft::mat4 getModel() const;
};

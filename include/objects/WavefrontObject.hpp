#pragma once
#include <vector>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

class WavefrontObject {
private:   
    std::vector<t_vbo_element> _data;
    VertexArray _vao;
    VertexBuffer _vbo;
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
    void move(ft::vec3 vec);
    std::vector<t_vbo_element> getData() const;
};

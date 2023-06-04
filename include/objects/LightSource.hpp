#pragma once
#include "../math/math.hpp"

class LightSource {
private:
    ft::vec3 _pos;
public:
    LightSource();
    LightSource(LightSource const &rhs);
    LightSource &operator=(LightSource const &rhs);
    ~LightSource();
    void setPos(ft::vec3 const &pos);
    ft::vec3 getPos() const;
};

#pragma once
#include "../math/math.hpp"

class Camera {
private:
    ft::vec3 _pos;
    ft::vec3 _dir;
public:
    Camera();
    Camera(Camera const &rhs);
    Camera &operator=(Camera const &rhs);
    ~Camera();
    void setPos(ft::vec3 const &pos);
    ft::vec3 getPos() const;
    void setDir(ft::vec3 const &dir);
    ft::vec3 getDir() const;
    void move(ft::vec3 const &vec);
    //TODO: Rotate function
};

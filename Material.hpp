#pragma once
#include <iostream>
class Material {
private:
    Material() {}
    Material(const Material &rhs) {}
    Material &operator=(const Material &rhs) {return *this;}
public:
    ~Material() {}
    Material(const std::string &src);
    void use();
};
#ifndef WFOBJECT_HPP
#define WFOBJECT_HPP

#include <vector>
#include "vec3.hpp"
#include "vec2.hpp"
class WFObject {
private:
    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec3> _v_texcoords;
    std::vector<ft::vec3> _v_normals;
    std::vector<int> _v_indices;
    ft::vec3 _ambient_color;
    ft::vec3 _diffuse_color;
    ft::vec3 _specular_color;
    WFObject();
    void trim_whitespace_after(std::string &s);
public:
    WFObject(std::string const &path);
};

#endif
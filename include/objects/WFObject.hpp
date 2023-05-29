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
    ft::vec3 _ambientColor;
    ft::vec3 _diffuseColor;
    ft::vec3 _specularColor;
    WFObject();
    void TrimWhitespaceAfter(std::string &s);
public:
    WFObject(std::string const &path);
};

#endif
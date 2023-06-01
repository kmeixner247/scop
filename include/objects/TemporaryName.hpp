#pragma once

#include <vector>
#include "../math/vec3.hpp"
#include "../math/vec2.hpp"
#include "Material.hpp"
#include "fstream"
class TemporaryName {
private:
    typedef struct s_vbo_element {
        ft::vec3 vertex;
        ft::vec2 texcoords;
        ft::vec3 normal;
    } t_vbo_element;
    typedef struct s_face {
        size_t offset;
        size_t size;
    } t_face;
    typedef void(TemporaryName::*handlerFunction)(std::string_view);
    std::map<std::string, handlerFunction> _lineHandlerMap;
    std::string _src;
    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec2> _v_texcoords;
    std::vector<ft::vec3> _v_normals;
    std::vector<Material> _v_mtllib;
    std::vector<t_vbo_element> _vbo;
    
    std::vector<int> _v_indices;
    std::vector<t_face> _faces;

    std::vector<Material> _parseMaterials(std::string const &src);
    void _readFileIntoString(std::string const &path);
    void _interpretLine(std::string_view const &lineView);
    void _initializeLineHandlerMap();
    void _handleMtllib(std::string_view lineView);
    void _handleVertex(std::string_view lineView);
    void _handleTextureCoordinate(std::string_view lineView);
    void _handleNormalVector(std::string_view lineView);
    void _handleObject(std::string_view lineView);
    void _handleGroup(std::string_view lineView);
    void _handleMaterial(std::string_view lineView);
    void _handleFace(std::string_view lineView);
    void _handleSmoothShading(std::string_view lineView);
    TemporaryName() {}
    TemporaryName(TemporaryName const &rhs) {}
    TemporaryName &operator=(TemporaryName const &rhs) { return *this; }
public:
    TemporaryName(std::string const &path);
    ~TemporaryName() {};
};
#pragma once

#include <vector>
#include "../math/vec3.hpp"
#include "../math/vec2.hpp"
#include "Material.hpp"
#include "fstream"
class TemporaryName {
private:
typedef void(TemporaryName::*handlerFunction)(std::string_view);
    std::map<std::string, handlerFunction> _lineHandlerMap;
    std::string _src;
    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec2> _v_texcoords;
    std::vector<ft::vec3> _v_normals;
    std::vector<int> _v_indices;
    std::vector<Material> _v_mtllib;

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
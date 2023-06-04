#pragma once

#include <vector>
#include <map>
#include "Material.hpp"
#include "../math/math.hpp"
#include "fstream"
#include "../scop.hpp"
#include "VertexBuffer.hpp"

class WavefrontObject {
private:   
    std::vector<t_vbo_element> _data;
    VertexBuffer _vbo;
public:
    WavefrontObject() {}
    WavefrontObject(WavefrontObject const &rhs) : _data(rhs._data) {}
    void draw() {
        _vbo.bind();
        glDrawArrays(GL_TRIANGLES, 0, size());
    }
    void push() {
        _vbo.push();
    }
    void add(t_vbo_element const &face) { _data.push_back(face); }
    int size() { return _data.size(); }
};

class WavefrontLoader {
private:

    typedef void(WavefrontLoader::*handlerFunction)(std::string_view);
    std::map<std::string, handlerFunction> _lineHandlerMap;
    std::string _src;
    std::map<std::string, std::map<int, WavefrontObject> > _objects;

    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec2> _v_texcoords;
    std::vector<ft::vec3> _v_normals;


    std::vector<Material> _v_mtllib;
    std::string _currentMaterial;


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

public:
    WavefrontLoader(std::string const &path);
};
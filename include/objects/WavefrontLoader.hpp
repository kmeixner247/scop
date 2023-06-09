#pragma once

#include <vector>
#include <map>
#include "Material.hpp"
#include "../math/math.hpp"
#include "fstream"
#include "../scop.hpp"
#include "../utils.hpp"
#include "WavefrontObject.hpp"
#include <random>
#include <stdexcept>

class Scene;

class WavefrontLoader {
private:

    typedef void(WavefrontLoader::*handlerFunction)(std::string_view);
    std::map<std::string, handlerFunction> _lineHandlerMap;
    std::string _src;
    std::map<std::string, WavefrontObject> _objects;

    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec2> _v_texcoords;
    std::vector<ft::vec3> _v_normals;


    std::vector<Material> _v_mtllib;
    std::string _currentMaterial;

    std::vector<ft::vec2> _rotateTriangleToXYPlane(std::vector<ft::vec3> triangle);
    std::vector<t_vbo_element> _createPoints(std::string_view lineView);
    ft::vec3 _findVertexCoordinate(std::string const &e);
    ft::vec2 _findTextureCoordinate(std::vector<std::string> const &e);
    ft::vec3 _findSurfaceNormal(std::vector<std::string> const &e);
    bool _surfaceNormalIsZero(std::vector<t_vbo_element> const &points);
    void _calculateSurfaceNormals(std::vector<t_vbo_element> &points);
    bool _textureCoordinateIsZero(std::vector<t_vbo_element> const &points);
    void _calculateTextureCoordinates(std::vector<t_vbo_element> &points);
    void _addFacesToObject(std::vector<t_vbo_element> const &points);
    void _parseMaterials(std::string const &src);
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
    void _centerObjects();
    WavefrontLoader() {}
    WavefrontLoader(WavefrontLoader const &rhs) {(void)rhs; }
    WavefrontLoader &operator=(WavefrontLoader const &rhs) { (void)rhs; return *this;}
public:
    WavefrontLoader(std::string const &path);
    ~WavefrontLoader();
    friend class Scene;
};
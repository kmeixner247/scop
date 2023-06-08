#include "../../include/objects/WavefrontLoader.hpp"
#include <random>
#include <stdexcept>

void WavefrontLoader::_readFileIntoString(std::string const &path) {
    std::stringstream ss;
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    ss << file.rdbuf();
    _src = ss.str();
}

void WavefrontLoader::_interpretLine(std::string_view const &lineView) {
    for (const auto &handler : _lineHandlerMap) {
        if (lineStartsWith(lineView, handler.first))
            (this->*handler.second)(lineView);
    }
}

void WavefrontLoader::_parseMaterials(std::string const &src) {
    std::stringstream ss;
    std::string path = "resources/" + src;
    std::ifstream file (path);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    std::string line;
    while (file && line.rfind("newmtl")) {
        getline(file, line);
    }
    while (file) {
        ss.str(std::string());
        do {
            ss << line << std::endl;
            getline(file, line);      
        } while (file && line.rfind("newmtl"));
        Material mat(ss.str());
        _v_mtllib.push_back(mat);
    }
}

void WavefrontLoader::_handleMtllib(std::string_view lineView) {
    removePrefixFrom(lineView, 7);
    _parseMaterials(std::string(lineView));
}

void WavefrontLoader::_handleVertex(std::string_view lineView) {
    removePrefixFrom(lineView, 2);
    _v_vertices.push_back(parseVec3(std::string(lineView)));
}

void WavefrontLoader::_handleTextureCoordinate(std::string_view lineView) {
    removePrefixFrom(lineView, 3);
    try {
        _v_texcoords.push_back(parseVec2(std::string(lineView)));
    }
    catch (std::exception const &e) {
        ft::vec3 texCoord3D = parseVec3(std::string(lineView));
        ft::vec2 texCoord2D(texCoord3D[0], texCoord3D[1]);
        _v_texcoords.push_back(texCoord2D);
    }
}

void WavefrontLoader::_handleNormalVector(std::string_view lineView) {
    removePrefixFrom(lineView, 3);
    _v_normals.push_back(parseVec3(std::string(lineView)));
}

void WavefrontLoader::_handleObject(std::string_view lineView) {
    removePrefixFrom(lineView, 2);
}

void WavefrontLoader::_handleGroup(std::string_view lineView) {
    removePrefixFrom(lineView, 2);
}

void WavefrontLoader::_handleMaterial(std::string_view lineView) {
    removePrefixFrom(lineView, 7);
    _currentMaterial = std::string(lineView);
    if (_objects.count(_currentMaterial) == 0) {
        _objects.insert(std::make_pair(_currentMaterial, WavefrontObject()));
    }
}

void WavefrontLoader::_handleFace(std::string_view lineView) {
    removePrefixFrom(lineView, 2);
    std::vector<t_vbo_element> temp;
    t_vbo_element point;
    point.randomColor.x = generateRandomNumber();
    point.randomColor.y = generateRandomNumber();
    point.randomColor.z = generateRandomNumber();
    std::vector<std::string> points = splitLineByCharacter(lineView, ' ');
    for (size_t i = 0; i < points.size(); i++) {
        std::vector<std::string> element = splitLineByCharacter(std::string_view(points[i]), '/');
        
        // TODO make nice

        // vertex coordinate
        size_t index = convertToInt(element[0]) - 1;
        if (index < 0)
            index += _v_vertices.size();
        if (index >= _v_vertices.size()) {
            throw std::runtime_error("Invalid vertex index in .obj file.");
        }
        point.vertex = _v_vertices[index];

        // texture coordinate
        if (element.size() > 1 && element[1].compare("")) {
            index = convertToInt(element[1]) - 1;
            if (index < 0)
                index += _v_texcoords.size();
            if (index >= _v_texcoords.size()) {
                throw std::runtime_error("Invalid texture coordinate index in .obj file.");
            }
            point.texCoords = _v_texcoords[index];
        }
        else
            point.texCoords = ft::vec2();

        // normal vector
        if (element.size() == 3) {
            index = convertToInt(element[2]) - 1;
            if (index < 0)
                index += _v_normals.size();
            if (index >= _v_normals.size()) {
                throw std::runtime_error("Invalid normal index in .obj file.");
            }
            point.normal = _v_normals[index];
        }
        else
            point.normal = ft::vec3();
        temp.push_back(point);
    }
    if (temp.size() == 0) {
        throw std::runtime_error("No valid faces in .obj file.");
    }
    if (temp[0].normal.x == 0 && temp[0].normal.y == 0 && temp[0].normal.z == 0) {
        ft::vec3 normal = ft::normalize(ft::crossproduct(temp[1].vertex - temp[0].vertex, temp[2].vertex - temp[1].vertex));
        for (size_t i = 0; i < temp.size(); i++)
            temp[i].normal = normal;
    }
    _objects[_currentMaterial].add(temp[0]);
    _objects[_currentMaterial].add(temp[1]);
    _objects[_currentMaterial].add(temp[2]);
    for (size_t i = 2; i < temp.size(); i++) {
        _objects[_currentMaterial].add(temp[0]);
        _objects[_currentMaterial].add(temp[i - 1]);
        _objects[_currentMaterial].add(temp[i]);
    }
}

void WavefrontLoader::_handleSmoothShading(std::string_view lineView) {
    removePrefixFrom(lineView, 2);
}

void WavefrontLoader::_initializeLineHandlerMap() {
    _lineHandlerMap["mtllib "] = &WavefrontLoader::_handleMtllib;
    _lineHandlerMap["v "] = &WavefrontLoader::_handleVertex;
    _lineHandlerMap["vt "] = &WavefrontLoader::_handleTextureCoordinate;
    _lineHandlerMap["vn "] = &WavefrontLoader::_handleNormalVector;
    _lineHandlerMap["o "] = &WavefrontLoader::_handleObject;
    _lineHandlerMap["g "] = &WavefrontLoader::_handleGroup;
    _lineHandlerMap["usemtl "] = &WavefrontLoader::_handleMaterial;
    _lineHandlerMap["f "] = &WavefrontLoader::_handleFace;
    _lineHandlerMap["s "] = &WavefrontLoader::_handleSmoothShading;
}

WavefrontLoader::WavefrontLoader(std::string const &path) : _currentMaterial("None") {
    try {
        _readFileIntoString(path);
        _initializeLineHandlerMap();

        _v_mtllib.push_back(Material());
        std::istringstream srcStream(_src);
        std::string line;
        std::string_view lineView;
        while (srcStream) {
            getline(srcStream, line);
            lineView = line;
            cutCommentsFrom(lineView);
            trimWhitespaceFrom(lineView);
            _interpretLine(lineView);
        }
        _centerObjects();
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        this->~WavefrontLoader();
        exit (-1);
    }
}

void WavefrontLoader::_centerObjects() {
    ft::vec3 center;
    int size = 0;
    for (auto obj : _objects) {
        size += obj.second.size();
        for (auto face : obj.second.getData()) {
            center += face.vertex;
        }
    }
    center /= size;
    center = -center;
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        it->second.move(center);
    }
}

WavefrontLoader::~WavefrontLoader() {
}
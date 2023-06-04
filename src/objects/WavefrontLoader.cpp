#include "../../include/objects/WavefrontLoader.hpp"
#include <random>

void WavefrontLoader::_readFileIntoString(std::string const &path) {
    std::stringstream ss;
    std::ifstream file(path);    
    ss << file.rdbuf();
    _src = ss.str();
}

void WavefrontLoader::_interpretLine(std::string_view const &lineView) {
    for (const auto &handler : _lineHandlerMap) {
        if (lineStartsWith(lineView, handler.first))
            (this->*handler.second)(lineView);
    }
}

std::vector<Material> WavefrontLoader::_parseMaterials(std::string const &src) {
    std::stringstream ss;
    std::ifstream file ("resources/" + src);
    std::string line;
    std::vector<Material> mats;
    mats.push_back(Material());
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
        mats.push_back(mat);
    }
    return mats;
}

void WavefrontLoader::_handleMtllib(std::string_view lineView) {
    lineView.remove_prefix(7);
    _v_mtllib = _parseMaterials(std::string(lineView));
}

void WavefrontLoader::_handleVertex(std::string_view lineView) {
    lineView.remove_prefix(2);
    _v_vertices.push_back(parseVec3(std::string(lineView)));
}

void WavefrontLoader::_handleTextureCoordinate(std::string_view lineView) {
    lineView.remove_prefix(3);
    _v_texcoords.push_back(parseVec2(std::string(lineView)));
}

void WavefrontLoader::_handleNormalVector(std::string_view lineView) {
    lineView.remove_prefix(3);
    _v_normals.push_back(parseVec3(std::string(lineView)));
}

void WavefrontLoader::_handleObject(std::string_view lineView) {
    lineView.remove_prefix(2);
}

void WavefrontLoader::_handleGroup(std::string_view lineView) {
    lineView.remove_prefix(2);
}

void WavefrontLoader::_handleMaterial(std::string_view lineView) {
    lineView.remove_prefix(7);
    _currentMaterial = std::string(lineView);
    if (_objects.count(_currentMaterial) == 0) {
        _objects.insert(std::make_pair(_currentMaterial, WavefrontObject()));
    }
}

void WavefrontLoader::_handleFace(std::string_view lineView) {
    lineView.remove_prefix(2);
    std::vector<t_vbo_element> temp;
    t_vbo_element point;
    point.randomColor.x = generateRandomNumber();
    point.randomColor.y = generateRandomNumber();
    point.randomColor.z = generateRandomNumber();
    size_t index;
    std::vector<std::string> points = splitLineByCharacter(lineView, ' ');
    for (int i = 0; i < points.size(); i++) {
        std::vector<std::string> element = splitLineByCharacter(std::string_view(points[i]), '/');
        
        // TODO make nice

        // vertex coordinate
        size_t index = std::stoi(element[0]) - 1;
        if (index < 0)
            index += _v_vertices.size();
        point.vertex = _v_vertices[index];

        // texture coordinate
        if (element.size() > 1 && element[1].compare("")) {
            index = std::stoi(element[1]) - 1;
            if (index < 0)
                index += _v_texcoords.size();
            point.texCoords = _v_texcoords[index];
        }
        else
            point.texCoords = ft::vec2();

        // normal vector
        if (element.size() == 3) {
            index = std::stoi(element[2]) - 1;
            if (index < 0)
                index += _v_normals.size();
            point.normal = _v_normals[index];
        }
        temp.push_back(point);
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
    lineView.remove_prefix(2);
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

WavefrontLoader::WavefrontLoader(std::string const &path) {
    _readFileIntoString(path);
    _initializeLineHandlerMap();

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
}

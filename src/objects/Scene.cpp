#include "../../include/objects/Scene.hpp"

void Scene::_readFileIntoString(std::string const &path) {
    std::stringstream ss;
    std::ifstream file(path);    
    ss << file.rdbuf();
    _src = ss.str();
}

void Scene::_interpretLine(std::string_view const &lineView) {
    for (const auto &handler : _lineHandlerMap) {
        if (lineStartsWith(lineView, handler.first))
            (this->*handler.second)(lineView);
    }
}

std::vector<Material> Scene::_parseMaterials(std::string const &src) {
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

void Scene::_handleMtllib(std::string_view lineView) {
    lineView.remove_prefix(7);
    _v_mtllib = _parseMaterials(std::string(lineView));
}

void Scene::_handleVertex(std::string_view lineView) {
    lineView.remove_prefix(2);
    _v_vertices.push_back(parseVec3(std::string(lineView)));
}

void Scene::_handleTextureCoordinate(std::string_view lineView) {
    lineView.remove_prefix(3);
    _v_texcoords.push_back(parseVec2(std::string(lineView)));
}

void Scene::_handleNormalVector(std::string_view lineView) {
    lineView.remove_prefix(3);
    _v_normals.push_back(parseVec3(std::string(lineView)));
}

void Scene::_handleObject(std::string_view lineView) {
    lineView.remove_prefix(2);
}

void Scene::_handleGroup(std::string_view lineView) {
    lineView.remove_prefix(2);
}

void Scene::_handleMaterial(std::string_view lineView) {
    lineView.remove_prefix(7);
}

void Scene::_handleFace(std::string_view lineView) {
    lineView.remove_prefix(2);
    t_vbo_element point;
    size_t index;
    std::vector<std::string> points = splitLineByCharacter(lineView, ' ');
    for (int i = 0; i < points.size(); i++) {
        std::vector<std::string> element = splitLineByCharacter(std::string_view(points[i]), '/');
        
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
        _vbo.push_back(point);
    }
}

void Scene::_handleSmoothShading(std::string_view lineView) {
    lineView.remove_prefix(2);
}

void Scene::_initializeLineHandlerMap() {
    _lineHandlerMap["mtllib "] = &Scene::_handleMtllib;
    _lineHandlerMap["v "] = &Scene::_handleVertex;
    _lineHandlerMap["vt "] = &Scene::_handleTextureCoordinate;
    _lineHandlerMap["vn "] = &Scene::_handleNormalVector;
    _lineHandlerMap["o "] = &Scene::_handleObject;
    _lineHandlerMap["g "] = &Scene::_handleGroup;
    _lineHandlerMap["usemtl "] = &Scene::_handleMaterial;
    _lineHandlerMap["f "] = &Scene::_handleFace;
    _lineHandlerMap["s "] = &Scene::_handleSmoothShading;
}

Scene::Scene(std::string const &path) {
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

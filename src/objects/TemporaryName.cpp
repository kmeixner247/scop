#include "../../include/objects/TemporaryName.hpp"

void TemporaryName::_readFileIntoString(std::string const &path) {
    std::stringstream ss;
    std::ifstream file(path);    
    ss << file.rdbuf();
    _src = ss.str();
}

void TemporaryName::_interpretLine(std::string_view const &lineView) {
    for (const auto &handler : _lineHandlerMap) {
        if (lineStartsWith(lineView, handler.first))
            (this->*handler.second)(lineView);
    }
}

std::vector<Material> TemporaryName::_parseMaterials(std::string const &src) {
    std::stringstream ss;
    std::ifstream file (src);
    std::string line;
    std::vector<Material> mats;
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

void TemporaryName::_handleMtllib(std::string_view lineView) {
    lineView.remove_prefix(7);
    _v_mtllib = _parseMaterials(std::string(lineView));
}

void TemporaryName::_handleVertex(std::string_view lineView) {
    lineView.remove_prefix(2);
    _v_vertices.push_back(parseVec3(std::string(lineView)));
    std::cout << "VERT"  << _v_vertices.size() << " " << _v_vertices.back() << std::endl;
}

void TemporaryName::_handleTextureCoordinate(std::string_view lineView) {
    lineView.remove_prefix(3);
    _v_texcoords.push_back(parseVec2(std::string(lineView)));
    std::cout << "TEX" << _v_texcoords.size() << " " << _v_texcoords.back() << std::endl;
}

void TemporaryName::_handleNormalVector(std::string_view lineView) {
    lineView.remove_prefix(3);
    _v_normals.push_back(parseVec3(std::string(lineView)));
    std::cout << "NORM" << _v_normals.size() << " " << _v_normals.back() << std::endl;
}

void TemporaryName::_handleObject(std::string_view lineView) {
    lineView.remove_prefix(2);
    std::cout << lineView << std::endl;
}

void TemporaryName::_handleGroup(std::string_view lineView) {
    lineView.remove_prefix(2);
    std::cout << lineView << std::endl;
}

void TemporaryName::_handleMaterial(std::string_view lineView) {
    lineView.remove_prefix(7);
    std::cout << lineView << std::endl;
}

void TemporaryName::_handleFace(std::string_view lineView) {
    lineView.remove_prefix(2);
    std::vector<std::string> points = splitLineByCharacter(lineView, ' ');
    for (int i = 0; i < points.size(); i++) {
        std::vector<std::string> element = splitLineByCharacter(std::string_view(points[i]), '/');
    }
}

void TemporaryName::_handleSmoothShading(std::string_view lineView) {
    lineView.remove_prefix(2);
    std::cout << lineView << std::endl;
}

void TemporaryName::_initializeLineHandlerMap() {
    _lineHandlerMap["mtllib "] = &TemporaryName::_handleMtllib;
    _lineHandlerMap["v "] = &TemporaryName::_handleVertex;
    _lineHandlerMap["vt "] = &TemporaryName::_handleTextureCoordinate;
    _lineHandlerMap["vn "] = &TemporaryName::_handleNormalVector;
    _lineHandlerMap["o "] = &TemporaryName::_handleObject;
    _lineHandlerMap["g "] = &TemporaryName::_handleGroup;
    _lineHandlerMap["usemtl "] = &TemporaryName::_handleMaterial;
    _lineHandlerMap["f "] = &TemporaryName::_handleFace;
    _lineHandlerMap["s "] = &TemporaryName::_handleSmoothShading;
}

TemporaryName::TemporaryName(std::string const &path) {
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
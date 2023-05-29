#include "../../include/objects/Material.hpp"

void Material::_handleName(std::string_view lineView) {
    lineView.remove_prefix(7);
    _name = std::string(lineView);
}

void Material::_handleNs(std::string_view lineView) {
    lineView.remove_prefix(3);
    _ns = std::stod(std::string(lineView));
}

void Material::_handleKa(std::string_view lineView) {
    lineView.remove_prefix(3);
    _ka = parseVector(lineView);
}

void Material::_handleKd(std::string_view lineView) {
    lineView.remove_prefix(3);
    _kd = parseVector(lineView);
}

void Material::_handleKs(std::string_view lineView) {
    lineView.remove_prefix(3);
    _ks = parseVector(lineView);
}

void Material::_handleKe(std::string_view lineView) {
    lineView.remove_prefix(3);
    _ke = parseVector(lineView);
}

void Material::_handleNi(std::string_view lineView) {
    lineView.remove_prefix(3);
    _ni = std::stod(std::string(lineView));
}

void Material::_handleD(std::string_view lineView) {
    lineView.remove_prefix(2);
    _d = std::stod(std::string(lineView));
}

void Material::_handleIllum(std::string_view lineView) {
    lineView.remove_prefix(6);
    _illum = std::stoi(std::string(lineView));
}

void Material::_initializeLineHandlerMap() {
    _lineHandlerMap["newmtl"] = &Material::_handleName;
    _lineHandlerMap["Ns"] = &Material::_handleNs;
    _lineHandlerMap["Ka"] = &Material::_handleKa;
    _lineHandlerMap["Kd"] = &Material::_handleKd;
    _lineHandlerMap["Ks"] = &Material::_handleKs;
    _lineHandlerMap["Ke"] = &Material::_handleKe;
    _lineHandlerMap["Ni"] = &Material::_handleNi;
    _lineHandlerMap["d"] = &Material::_handleD;
    _lineHandlerMap["illum"] = &Material::_handleIllum;
}



void Material::_interpretLine(std::string_view const &lineView) {
    for (const auto &handler : _lineHandlerMap) {
        if (lineStartsWith(lineView, handler.first))
            (this->*handler.second)(lineView);
    }
}

Material::Material(const std::string &src) {
    std::istringstream srcStream(src);
    std::string line;
    std::string_view lineView;
    _initializeLineHandlerMap();
    while (srcStream) {
        getline(srcStream, line);
        lineView = line;
        _cutCommentsFrom(lineView);
        _trimWhitespaceFrom(lineView);
        _interpretLine(lineView);
    }
}

Material::Material() : 
_name(""), 
_ns(0), 
_ka(ft::vec3(0)), 
_kd(ft::vec3(0)), 
_ks(ft::vec3(0)),
_ke(ft::vec3(0)),
_ni(0),
_d(0),
_illum(0) {
    _initializeLineHandlerMap();
}

Material::Material(Material const &rhs) : 
_name(rhs._name),
_ns(rhs._ns),
_kd(rhs._kd),
_ka(rhs._ka),
_ks(rhs._ks),
_ke(rhs._ke),
_ni(rhs._ni),
_d(rhs._d),
_illum(rhs._illum) {
    _initializeLineHandlerMap();
}

Material &Material::operator=(const Material &rhs) {
    _name = rhs._name;
    _ns = rhs._ns;
    _kd = rhs._kd;
    _ka = rhs._ka;
    _ks = rhs._ks;
    _ke = rhs._ke;
    _ni = rhs._ni;
    _d = rhs._d;
    _illum = rhs._illum;
    return *this;
}

Material::~Material() {}
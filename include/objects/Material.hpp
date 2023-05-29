#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "../vec3.hpp"
#include "../scop.hpp"
class Material {
private:
    typedef void (Material::*handlerFunction)(std::string_view);
    std::map<std::string, handlerFunction> _lineHandlerMap;
    std::string _name;
    double _ns;
    ft::vec3 _ka;
    ft::vec3 _kd;
    ft::vec3 _ks;
    ft::vec3 _ke;
    double _ni;
    double _d;
    int _illum;

    ft::vec3 _parseVector(std::string_view const &lineView);
    void _initializeLineHandlerMap();
    void _handleName(std::string_view lineView);
    void _handleNs(std::string_view lineView);
    void _handleKa(std::string_view lineView);
    void _handleKd(std::string_view lineView);
    void _handleKs(std::string_view lineView);
    void _handleKe(std::string_view lineView);
    void _handleNi(std::string_view lineView);
    void _handleD(std::string_view lineView);
    void _handleIllum(std::string_view lineView);
    bool _lineStartsWith(std::string_view const &strView, const std::string prefix);
    void _cutCommentsFrom(std::string_view &lineView);
    void _trimWhitespaceFrom(std::string_view &lineView);
    void _interpretLine(std::string_view const &lineView);
    std::vector<std::string> _splitLineByCharacter(std::string_view lineView, char del);

public:
    Material();
    Material(const Material &rhs);
    Material &operator=(const Material &rhs);
    ~Material();
    Material(const std::string &src);
    void use();
};
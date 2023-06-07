#include "../include/scop.hpp"
#include <random>

int convertToInt(std::string const &val) {
    try {
        return std::stoi(val);
    }
    catch (const std::exception &e) {
        throw std::runtime_error("stoi: no valid conversion of '" + val + "'.");
    }
}
float convertToFloat(std::string const &val) {
    try {
        return std::stod(val);
    }
    catch (const std::exception &e) {
        throw std::runtime_error("stod: no valid conversion of '" + val + "'.");
    }
}

std::vector<std::string> splitLineByCharacter(std::string_view lineView, char del) {
    std::vector<std::string> vals;
    size_t pos;
    do {
        pos = lineView.find(del);
        vals.push_back(std::string((lineView.substr(0, pos))));
        lineView.remove_prefix(pos+1);
    }   while (pos != std::string::npos);
    return vals;
}
ft::vec2 parseVec2(std::string_view const &lineView) {
    std::vector<std::string> vals = splitLineByCharacter(lineView, ' ');
    if (vals.size() != 2) {
        throw std::runtime_error("parseVec2: invalid vector size.");
    }
    return ft::vec2(convertToFloat(vals[0]), convertToFloat(vals[1]));
}

ft::vec3 parseVec3(std::string_view const &lineView) {
    std::vector<std::string> vals = splitLineByCharacter(lineView, ' ');
    if (vals.size() != 3) {
        throw std::runtime_error("parseVec3: invalid vector size.");
    }
    return ft::vec3(convertToFloat(vals[0]), convertToFloat(vals[1]), convertToFloat(vals[2]));
}

ft::vec4 parseVec4(std::string_view const &lineView) {
    std::vector<std::string> vals = splitLineByCharacter(lineView, ' ');
    if (vals.size() != 4) {
        throw std::runtime_error("parseVec4: invalid vector size.");
    }
    return ft::vec4(convertToFloat(vals[0]), convertToFloat(vals[1]), convertToFloat(vals[2]), convertToFloat(vals[3]));
}

bool lineStartsWith(std::string_view const &strView, const std::string prefix) {
    return !strView.rfind(prefix);
}

void cutCommentsFrom(std::string_view &lineView) {
    auto commentPos = lineView.find('#');
    if (commentPos != lineView.npos)
        lineView.remove_suffix(lineView.size() - commentPos);
}

void trimWhitespaceFrom(std::string_view &lineView) {
    auto endPos = lineView.find_last_not_of(" \t\n\v\f\r");
    if (endPos <= lineView.size())
        lineView.remove_suffix(lineView.size() - endPos - 1);
}

float generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}
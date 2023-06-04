#include "../include/scop.hpp"
#include <random>

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
    return ft::vec2(std::stod(vals[0]), std::stod(vals[1]));
}

ft::vec3 parseVec3(std::string_view const &lineView) {
    std::vector<std::string> vals = splitLineByCharacter(lineView, ' ');
    return ft::vec3(std::stod(vals[0]), std::stod(vals[1]), std::stod(vals[2]));
}

ft::vec4 parseVec4(std::string_view const &lineView) {
    std::vector<std::string> vals = splitLineByCharacter(lineView, ' ');
    return ft::vec4(std::stod(vals[0]), std::stod(vals[1]), std::stod(vals[2]), std::stod(vals[3]));
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

void readFileIntoString(std::string const &path, std::string &dest) {
    std::stringstream ss;
    std::ifstream file(path);
    ss << file.rdbuf();
    dest = ss.str();
}

float generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}
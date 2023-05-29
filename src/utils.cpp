#include "scop.hpp"

ft::vec3 parseVector(std::string_view const &lineView) {
    std::vector<std::string> vals = splitLineByCharacter(lineView, ' ');
    return ft::vec3(std::stod(vals[0]), std::stod(vals[1]), std::stod(vals[2]));
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

std::vector<std::string> splitLineByCharacter(std::string_view lineView, char del) {
    std::vector<std::string> vals;
    size_t pos;
    for (size_t i = 0; i < 3; i++) {
        pos = lineView.find(' ');
        vals.push_back(std::string((lineView.substr(0, pos))));
        lineView.remove_prefix(pos+1);
    }
    return vals;
}
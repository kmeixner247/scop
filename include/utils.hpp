#pragma once

#include "math/math.hpp"

ft::vec3 parseVector(std::string_view const &lineView);
bool lineStartsWith(std::string_view const &strView, const std::string prefix);
void cutCommentsFrom(std::string_view &lineView);
void trimWhitespaceFrom(std::string_view &lineView);
std::vector<std::string> splitLineByCharacter(std::string_view lineView, char del);
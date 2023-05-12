#include "WFObject.hpp"
#include <fstream>
#include <iostream>
#include <string>


void WFObject::trim_whitespace_after(std::string &s) {
	size_t pos = s.find_last_not_of(" \t\n\v\f\r");
	if (pos != std::string::npos && pos != s.size() - 1)
		s.erase(s.begin() + pos + 1, s.end());
}


WFObject::WFObject(std::string const &path) {
    std::ifstream file(path);
    std::vector<std::string> v_lines;
    std::string str;

    while (file) {
        std::getline(file, str);
        if (file) {
            trim_whitespace_after(str);
            v_lines.push_back(str);
            std::cout << (str.size()) << std::endl;
        }
    }
    for (auto line : v_lines) {

        // std::cout << line << std::endl;
    }
}
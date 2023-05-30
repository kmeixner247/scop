#include "../include/objects/Material.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::vector<Material> parseMaterials(std::string const &src) {
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


int main() {
    std::vector<Material> mats = parseMaterials("test2.mtl");
    std::cout << mats.size() << std::endl;
}
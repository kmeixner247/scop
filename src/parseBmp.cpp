// main.cpp

#include "bmpParser.hpp"
#include <fstream>
#include <sstream>
struct s_bmp parseBmp(std::string const &path) {
    s_bmp mybmp;
    struct bmp_header BMP_HEAD;
    struct dib_header DIB_HEAD;
    std::ifstream file(path, std::ios::binary);
    file.read(reinterpret_cast<char*>(&mybmp.bmpHeader), sizeof(struct bmp_header));
    file.read(reinterpret_cast<char*>(&mybmp.dibHeader), sizeof(struct dib_header));
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    std::string str = ss.str();
    struct s_pixel pxl;
    while (str.size() > 0) {
        pxl.r = str[2];
        pxl.g = str[1];
        pxl.b = str[0];
        mybmp.pixelData.push_back(pxl);
        str.erase(0,3);
    }
    return mybmp;
}

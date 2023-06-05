// main.cpp

#include "../include/bmpParser.hpp"
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
    const char *pixels = str.c_str();
    for (int i = 0; i < str.size(); i += 3) {
        pxl.r = pixels[i];
        pxl.g = pixels[i+1];
        pxl.b = pixels[i+2];
        mybmp.pixelData.push_back(pxl);
    }
    return mybmp;
}

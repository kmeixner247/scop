#include "../../include/objects/Texture.hpp"
#include <OpenGL/gl3.h>

#include <fstream>
#include <sstream>
#include <iostream>
Texture::Texture() {
}
Texture::Texture(Texture const &rhs) {
    *this = rhs;
}
Texture::Texture(std::string const &path) {
    generate(path);
}

void Texture::printInfo() const {
    std::cout << "signature: " << _bmp.bmpHeader.signature[0] <<_bmp.bmpHeader.signature[1] << std::endl;
    std::cout << "fileSize: " << _bmp.bmpHeader.fileSize << std::endl;
    std::cout << "reserved1: " << _bmp.bmpHeader.reserved1 << std::endl;
    std::cout << "reserved2: " << _bmp.bmpHeader.reserved2 << std::endl;
    std::cout << "offset: " << _bmp.bmpHeader.offset << std::endl;

    std::cout << "headerSize: " << _bmp.dibHeader.headerSize << std::endl;
    std::cout << "width: " << _bmp.dibHeader.width << std::endl;
    std::cout << "height: " << _bmp.dibHeader.height << std::endl;
    std::cout << "colorPlanes: " << _bmp.dibHeader.colorPlanes << std::endl;
    std::cout << "bitsPerPixel: " << _bmp.dibHeader.bitsPerPixel << std::endl;
    std::cout << "compressionMethod: " << _bmp.dibHeader.compressionMethod << std::endl;
    std::cout << "imageSize: " << _bmp.dibHeader.imageSize << std::endl;
    std::cout << "horizontalResolution: " << _bmp.dibHeader.horizontalResolution << std::endl;
    std::cout << "verticalResolution: " << _bmp.dibHeader.verticalResolution << std::endl;
    std::cout << "numColors: " << _bmp.dibHeader.numColors << std::endl;
    std::cout << "numImportantColors: " << _bmp.dibHeader.numImportantColors << std::endl;
}

Texture &Texture::operator=(Texture const &rhs) {
    _id = rhs._id;
    _bmp.bmpHeader.signature[0] = rhs._bmp.bmpHeader.signature[0];
    _bmp.bmpHeader.signature[1] = rhs._bmp.bmpHeader.signature[1];
    _bmp.bmpHeader.fileSize = rhs._bmp.bmpHeader.fileSize;
    _bmp.bmpHeader.reserved1 = rhs._bmp.bmpHeader.reserved1;
    _bmp.bmpHeader.reserved2 = rhs._bmp.bmpHeader.reserved2;
    _bmp.bmpHeader.offset = rhs._bmp.bmpHeader.offset;

    _bmp.dibHeader.headerSize = rhs._bmp.dibHeader.headerSize;
    _bmp.dibHeader.width = rhs._bmp.dibHeader.width;
    _bmp.dibHeader.height = rhs._bmp.dibHeader.height;
    _bmp.dibHeader.colorPlanes = rhs._bmp.dibHeader.colorPlanes;
    _bmp.dibHeader.bitsPerPixel = rhs._bmp.dibHeader.bitsPerPixel;
    _bmp.dibHeader.compressionMethod = rhs._bmp.dibHeader.compressionMethod;
    _bmp.dibHeader.imageSize = rhs._bmp.dibHeader.imageSize;
    _bmp.dibHeader.horizontalResolution = rhs._bmp.dibHeader.horizontalResolution;
    _bmp.dibHeader.verticalResolution = rhs._bmp.dibHeader.verticalResolution;
    _bmp.dibHeader.numColors = rhs._bmp.dibHeader.numColors;
    _bmp.dibHeader.numImportantColors = rhs._bmp.dibHeader.numImportantColors;

    _bmp.pixelData = rhs._bmp.pixelData;
    return *this;
};

Texture::~Texture() {}

void Texture::parseBmp(std::string const &path) {
    std::ifstream file(path, std::ios::binary);
    file.read(reinterpret_cast<char*>(&_bmp.bmpHeader), sizeof(struct bmp_header));
    file.read(reinterpret_cast<char*>(&_bmp.dibHeader), sizeof(struct dib_header));
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    std::string str = ss.str();
    struct s_pixel pxl;
    const char *pixels = str.c_str();
    for (size_t i = 0; i < str.size(); i += 3) {
        pxl.r = pixels[i];
        pxl.g = pixels[i+1];
        pxl.b = pixels[i+2];
        _bmp.pixelData.push_back(pxl);
    }
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, _id); 
}

void Texture::generate(std::string const &path) {
    parseBmp(path);
	glGenTextures(1, &_id);
    bind();
	int twidth, theight;
	twidth = _bmp.dibHeader.width;
	theight = _bmp.dibHeader.height;
	char *tdata = reinterpret_cast<char*>(&_bmp.pixelData[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
	glGenerateMipmap(GL_TEXTURE_2D);
}
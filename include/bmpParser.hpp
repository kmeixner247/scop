// bmpParser.hpp

#pragma once

#include <vector>

#pragma pack(1)
struct s_pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct bmp_header {
    unsigned char signature[2];
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
};

struct dib_header {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short colorPlanes;
    unsigned short bitsPerPixel;
    unsigned int compressionMethod;
    unsigned int imageSize;
    unsigned int horizontalResolution;
    unsigned int verticalResolution;
    unsigned int numColors;
    unsigned int numImportantColors;
};

typedef struct s_bmp {
    struct bmp_header bmpHeader;
    struct dib_header dibHeader;
    std::vector<s_pixel> pixelData;
} t_bmp;
#pragma pack()
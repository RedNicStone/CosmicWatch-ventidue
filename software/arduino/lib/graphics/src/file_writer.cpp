//
// Created by nic on 06/07/22.
//

#include <cstring>
#include <cstdio>

#include "file_writer.h"


void FileWriter::writeToArray(unsigned char *dst, const unsigned char *image, unsigned int width, unsigned int height) {
    auto filesize = getFilesize(width, height);

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(width       );
    bmpinfoheader[ 5] = (unsigned char)(width  >>  8);
    bmpinfoheader[ 6] = (unsigned char)(width  >> 16);
    bmpinfoheader[ 7] = (unsigned char)(width  >> 24);
    bmpinfoheader[ 8] = (unsigned char)(height      );
    bmpinfoheader[ 9] = (unsigned char)(height >>  8);
    bmpinfoheader[10] = (unsigned char)(height >> 16);
    bmpinfoheader[11] = (unsigned char)(height >> 24);

    std::memcpy(dst     ,bmpfileheader,14);
    std::memcpy(dst + 14,bmpinfoheader,40);
    std::memcpy(dst + 54,image        ,width * height * 3);
}

void FileWriter::writeImageToFile(const char *filename,
                                  const unsigned char *image,
                                  unsigned int width,
                                  unsigned int height) {
    size_t filesize = getFilesize(width, height);
    auto* data = new unsigned char[filesize];

    writeToArray(data, image, width, height);

    auto file = fopen(filename, "wb");
    fwrite(data, 1, filesize, file);
    fclose(file);

    delete[] data;
}

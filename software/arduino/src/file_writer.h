//
// Created by RedNicStone on 06/07/22.
//

#pragma once

#ifndef GRAPHICS_WRITE_FILE_H
#define GRAPHICS_WRITE_FILE_H

#include <cstring>

#include "graphics/renderer/stream_converters.h"

class FileWriter {
  private:
    static void writeToArray(unsigned char *dst, unsigned int width, unsigned int height);

    static size_t getFilesize(unsigned int width, unsigned int height) { return 54 + 3 * width * height; }

  public:
    template<StreamSignature<RGB8> Source>
    static void writeImageToFile(const char* filename,
                                 Source src,
                                 unsigned int width,
                                 unsigned int height);

    static void writeImageToFile(const char* filename,
                                 const std::function<RGB8(const Point2D&)>& src,
                                 unsigned int width,
                                 unsigned int height);
};

void FileWriter::writeToArray(unsigned char *dst, unsigned int width, unsigned int height) {
    auto filesize = getFilesize(width, height);

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

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
}

template<StreamSignature<RGB8> Source>
void FileWriter::writeImageToFile(const char *filename,
                                  Source src,
                                  unsigned int width,
                                  unsigned int height) {
    size_t filesize = getFilesize(width, height);
    auto* data = new unsigned char[filesize];

    writeToArray(data, width, height);
    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++) {
            RGB8 color = src.operator() (Point2D(x, y));
            std::memcpy(data + 54 + (x + y * width) * 3, color.data(), 3);
        }

    auto file = fopen(filename, "wb");
    fwrite(data, 1, filesize, file);
    fclose(file);

    delete[] data;
}

void FileWriter::writeImageToFile(const char *filename,
                                  const std::function<RGB8(const Point2D&)>& src,
                                  unsigned int width,
                                  unsigned int height) {
    size_t filesize = getFilesize(width, height);
    auto* data = new unsigned char[filesize];

    writeToArray(data, width, height);
    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++) {
            RGB8 color = src(Point2D(x, y));
            std::memcpy(data + 54 + (x + y * width) * 3, color.data(), 3);
        }

    auto file = fopen(filename, "wb");
    fwrite(data, 1, filesize, file);
    fclose(file);

    delete[] data;
}

#endif //GRAPHICS_WRITE_FILE_H

//
// Created by nic on 06/07/22.
//

#include <iostream>

#include "../../src/file_writer.h"


int main() {
    int height = 128;
    int width = 128;
    unsigned char image[height][width][3];

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            image[i][j][2] = (unsigned char) ( i * 255 / height );
            image[i][j][1] = (unsigned char) ( j * 255 / width );
            image[i][j][0] = (unsigned char) ( (i+j) * 255 / (height+width) );
        }
    }

    FileWriter::writeImageToFile("demo.bmp", (const unsigned char *)(image), width, height);

    system("feh demo.bmp --zoom 1000 --force-aliasing");
}


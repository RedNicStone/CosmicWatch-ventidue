//
// Created by nic on 06/07/22.
//

#ifndef GRAPHICS_WRITE_FILE_H
#define GRAPHICS_WRITE_FILE_H

class FileWriter {
  private:
    static void writeToArray(unsigned char *dst, const unsigned char* image, unsigned int width, unsigned int height);

    static size_t getFilesize(unsigned int width, unsigned int height) { return 54 + 3 * width * height; }

  public:
    static void writeImageToFile(const char* filename,
                                 const unsigned char* image,
                                 unsigned int width,
                                 unsigned int height);
};

#endif //GRAPHICS_WRITE_FILE_H

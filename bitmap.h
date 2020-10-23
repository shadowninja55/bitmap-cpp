#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include <string>

namespace bmp {
    std::vector<std::vector<int>> readBitmap(std::string filename);
    void writeBitmap(std::vector<std::vector<int>> pixels, std::string filename);
}

#endif
# bitmap
A single C++ header file that adds an easy way to read and write bitmaps using 2D integer vectors.

# documentation
`std::vector<std::vector<int>> bmp::readBitmap(std::string filename)` - Reads the specified bitmap image and returns as a 2D vector of integers.
`void bmp::writeBitmap(std::vector<std::vector<int>> pixels, std::string filename)` - Writes the specified 2D integer array into the specified bitmap image.

# notes
- Header currently only supports 24-bit RGB bitmaps.
- Header assumes little-endian processor.

# usage (g++)
Make sure to `#include "bitmap.h"` in your main file, and then compile using `g++ main.cpp bitmap.cpp`.

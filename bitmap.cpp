#include "bitmap.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

int bint(vector<unsigned char> bytes) {
    int decimal = 0;
    for (int i = 0; i < bytes.size(); i++) 
        decimal += bytes[i] << (i * 8);

    return decimal;
}

vector<unsigned char> ibytes(int decimal, int count) {
    vector<unsigned char> bytes(count);
    memcpy(&bytes[0], &decimal, sizeof decimal);
    return bytes;
}

void fdwrite(int decimal, int count, FILE* file) {
    vector<unsigned char> bytes = ibytes(decimal, count);
    fwrite(&bytes[0], 1, count, file);
}

int fdread(int count, FILE* file) {
    vector<unsigned char> bytes(count);
    fread(&bytes[0], 1, count, file);
    return bint(bytes);
}

vector<vector<int>> bmp::readBitmap(string filename) {
    FILE* file = fopen(filename.c_str(), "rb");

    // reading header
    fseek(file, 18, SEEK_SET); // seek to width / height
    int width = fdread(4, file); // reading width
    int height = fdread(4, file); // reading height
    
    // reading pixels
    fseek(file, 54, SEEK_SET); // seek to pixel data
    vector<vector<int>> pixels(height);

    for (int y = 0; y < height; y++) {
        vector<int> row(width);
        for (int x = 0; x < width; x++) 
            row[x] = fdread(3, file);
    
        pixels[y] = row;
    }
    
    reverse(pixels.begin(), pixels.end());
    fclose(file);

    return pixels;
}

void bmp::writeBitmap(vector<vector<int>> pixels, string filename) {
    int width = pixels[0].size();
    int height = pixels.size();

    FILE* file = fopen(filename.c_str(), "wb");
    
    // header
    fwrite(new unsigned char[2] {'B', 'M'}, 1, 2, file); // signature
    fdwrite(width * height * 3 + 54, 4, file); // file size
    fdwrite(0, 4, file); // reserved
    fdwrite(54, 4, file); // data offset

    // info header
    fdwrite(40, 4, file); // size
    fdwrite(width, 4, file); // width
    fdwrite(height, 4, file); // height
    fdwrite(1, 2, file); // planes
    fdwrite(24, 2, file); // bits per pixel
    fdwrite(0, 16, file); // compression, image size, x ppm, y ppm
    fdwrite(0xffffff, 4, file); // colors used
    fdwrite(0, 4, file); // important colors

    int padWidth = 4 - ((width * 3) % 4);

    if (padWidth < 4) { // writing with padding
        for (auto row = pixels.rbegin(); row != pixels.rend(); row++) {
            for (auto decimal : *row) {
                fdwrite(decimal, 3, file);
            }
            fdwrite(0, padWidth, file);
        }
    } else { // writing without padding
        for (auto row = pixels.rbegin(); row != pixels.rend(); row++) 
            for (auto decimal : *row) 
                fdwrite(decimal, 3, file);
    }

    fclose(file);
}



    
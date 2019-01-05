#pragma once 

#include <string>

struct Frame {
    std::string filename;
    int offsetX, offsetY, w, h;
    Frame(int offsetX, int offsetY, int w, int h, std::string filename)
        : filename(filename), offsetX(offsetX), offsetY(offsetY), w(w), h(h) {}
};

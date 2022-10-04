#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "BitmapPixels.hpp"

void BitmapPixels::readBitmapPixels(std::ifstream &fs, std::uint32_t height, std::uint32_t width, std::uint16_t bitDepth) {
    if (bitDepth == 0x04) {
        width /= 0x02;
    }

    for (int i = 0; i < static_cast<int>(height); i++) {
        std::vector<std::uint8_t> line;

        for (int j = 0; j < static_cast<int>(width); j++) {
            if (bitDepth == 0x08) {
                std::uint8_t pixel;
                fs.read(reinterpret_cast<char *>(&pixel), 0x01);
                line.push_back(pixel);
            }
            else if (bitDepth == 0x04) {
                std::uint8_t twoPixels;
                fs.read(reinterpret_cast<char *>(&twoPixels), 0x01);
                std::uint8_t pixelOne = (twoPixels & 0xF0) >> 0x04;
                std::uint8_t pixelTwo = twoPixels & 0x0F;
                line.push_back(pixelOne);
                line.push_back(pixelTwo);
            }
        }
        pixels.push_back(line);
    }
}

void BitmapPixels::writeBitmapPixels(std::ofstream &fs, std::uint32_t height, std::uint32_t width, std::uint16_t bitDepth) const {
    int stride = 1;

    if (bitDepth == 0x04) {
        stride = 2;
    }

    for (int i = 0; i < static_cast<int>(height); i++) {
        for (int j = 0; j < static_cast<int>(width); j += stride) {
            if (bitDepth == 0x08) {
                fs.write(reinterpret_cast<const char *>(&pixels.at(i).at(j)), 0x01);
            }
            else if (bitDepth == 0x04) {
                std::uint8_t pixelOne = pixels.at(i).at(j) << 0x04;
                std::uint8_t pixelTwo = pixels.at(i).at(j + 0x01);
                std::uint8_t twoPixels;
                twoPixels = pixelOne | pixelTwo;
                fs.write(reinterpret_cast<const char *>(&twoPixels), 0x01);
            }
        }
    }
}

const std::vector<std::vector<std::uint8_t>> &BitmapPixels::getPixels() const {
    return pixels;
}

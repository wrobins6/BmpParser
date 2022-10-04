#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "BitmapPalette.hpp"

void BitmapPalette::readBitmapPalette(std::ifstream &fs, std::uint32_t size) {
    for (int i = 0; i < static_cast<int>(size); i++) {
        Bitmap32BitColor color;
        fs.read(reinterpret_cast<char *>(&color.red), 0x01);
        fs.read(reinterpret_cast<char *>(&color.green), 0x01);
        fs.read(reinterpret_cast<char *>(&color.blue), 0x01);
        fs.read(reinterpret_cast<char *>(&color.reserved), 0x01);
        palette.push_back(color);
    }
}

void BitmapPalette::writeBitmapPalette(std::ofstream &fs, std::uint32_t size) const {
    for (int i = 0; i < static_cast<int>(size); i++) {
        fs.write(reinterpret_cast<const char *>(&palette.at(i).red), 0x01);
        fs.write(reinterpret_cast<const char *>(&palette.at(i).green), 0x01);
        fs.write(reinterpret_cast<const char *>(&palette.at(i).blue), 0x01);
        fs.write(reinterpret_cast<const char *>(&palette.at(i).reserved), 0x01);
    }
}

const std::vector<Bitmap32BitColor> &BitmapPalette::getPalette() const {
    return palette;
}

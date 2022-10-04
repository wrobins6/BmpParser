#ifndef BITMAPPIXELS_HPP
#define BITMAPPIXELS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

class BitmapPixels {
    private:
        std::vector<std::vector<std::uint8_t>> pixels;

    public:
        void readBitmapPixels(std::ifstream &fs, std::uint32_t height, std::uint32_t width, std::uint16_t bitDepth);
        void writeBitmapPixels(std::ofstream &fs, std::uint32_t height, std::uint32_t width, std::uint16_t bitDepth) const;
        const std::vector<std::vector<std::uint8_t>> &getPixels() const;
};

#endif

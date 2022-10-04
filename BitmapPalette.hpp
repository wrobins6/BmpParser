#ifndef BITMAPPALETTE_HPP
#define BITMAPPALETTE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct Bitmap32BitColor {
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t reserved;
};

class BitmapPalette {
    private:
        std::vector<Bitmap32BitColor> palette;

    public:
        void readBitmapPalette(std::ifstream &fs, std::uint32_t size);
        void writeBitmapPalette(std::ofstream &fs, std::uint32_t size) const;
        const std::vector<Bitmap32BitColor> &getPalette() const;
};

#endif

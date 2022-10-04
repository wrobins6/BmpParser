#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "BitmapPalette.hpp"
#include "BitmapPixels.hpp"

struct BitmapFileHeader {
    const std::uint16_t signature = 0x4D42;
    std::uint32_t fileSize;
    std::uint16_t reserved1;
    std::uint16_t reserved2;
    std::uint32_t dataOffset;
};

struct BitmapInfoHeader {
    std::uint32_t infoHeaderSize;
    std::uint32_t width;
    std::uint32_t height;
    std::uint16_t planes;
    std::uint16_t bitsPerPixel;
    std::uint32_t compression;
    std::uint32_t imageSize;
    std::uint32_t xPixelsPerMeter;
    std::uint32_t yPixelsPerMeter;
    std::uint32_t colorsUsed;
    std::uint32_t importantColors;
};

class Bitmap {
    private:
        BitmapFileHeader fileHeader;
        BitmapInfoHeader infoHeader;
        BitmapPalette colorTable;
        BitmapPixels pixelData;

    public:
        bool readBitmap(std::ifstream &fs);
        void writeBitmap(std::ofstream &fs) const;
        std::uint32_t getHeight() const;
        std::uint32_t getWidth() const;
        std::uint16_t getBitsPerPixel() const;
        const Bitmap32BitColor &getColor(int index) const;
        std::uint8_t getPixel(int indexOne, int indexTwo) const;
};

#endif

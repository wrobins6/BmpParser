#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "Bitmap.hpp"
#include "BitmapPalette.hpp"
#include "BitmapPixels.hpp"

bool Bitmap::readBitmap(std::ifstream &fs) {
    std::uint16_t signature;
    fs.read(reinterpret_cast<char *>(&signature), 0x02);

    if (fileHeader.signature != signature) {
        return false;
    }

    fs.read(reinterpret_cast<char *>(&fileHeader.fileSize), 0x04);
    fs.read(reinterpret_cast<char *>(&fileHeader.reserved1), 0x02);
    fs.read(reinterpret_cast<char *>(&fileHeader.reserved2), 0x02);
    fs.read(reinterpret_cast<char *>(&fileHeader.dataOffset), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.infoHeaderSize), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.width), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.height), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.planes), 0x02);
    fs.read(reinterpret_cast<char *>(&infoHeader.bitsPerPixel), 0x02);
    fs.read(reinterpret_cast<char *>(&infoHeader.compression), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.imageSize), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.xPixelsPerMeter), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.yPixelsPerMeter), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.colorsUsed), 0x04);
    fs.read(reinterpret_cast<char *>(&infoHeader.importantColors), 0x04);

    if (infoHeader.bitsPerPixel == 0x08) {
        colorTable.readBitmapPalette(fs, 0x100);
    }

    else if (infoHeader.bitsPerPixel == 0x04) {
        colorTable.readBitmapPalette(fs, 0x10);
    }

    fs.seekg(fileHeader.dataOffset, std::ios::beg);

    pixelData.readBitmapPixels(fs, infoHeader.height, infoHeader.width, infoHeader.bitsPerPixel);

    return true;
}

void Bitmap::writeBitmap(std::ofstream &fs) const {
    fs.write(reinterpret_cast<const char *>(&fileHeader.signature), 0x02);
    fs.write(reinterpret_cast<const char *>(&fileHeader.fileSize), 0x04);
    fs.write(reinterpret_cast<const char *>(&fileHeader.reserved1), 0x02);
    fs.write(reinterpret_cast<const char *>(&fileHeader.reserved2), 0x02);
    fs.write(reinterpret_cast<const char *>(&fileHeader.dataOffset), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.infoHeaderSize), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.width), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.height), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.planes), 0x02);
    fs.write(reinterpret_cast<const char *>(&infoHeader.bitsPerPixel), 0x02);
    fs.write(reinterpret_cast<const char *>(&infoHeader.compression), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.imageSize), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.xPixelsPerMeter), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.yPixelsPerMeter), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.colorsUsed), 0x04);
    fs.write(reinterpret_cast<const char *>(&infoHeader.importantColors), 0x04);

    if (infoHeader.bitsPerPixel == 0x08) {
        colorTable.writeBitmapPalette(fs, 0x100);
    }

    else if (infoHeader.bitsPerPixel == 0x04) {
        colorTable.writeBitmapPalette(fs, 0x10);
    }

    pixelData.writeBitmapPixels(fs, infoHeader.height, infoHeader.width, infoHeader.bitsPerPixel);
}

std::uint32_t Bitmap::getHeight() const {
    return infoHeader.height;
}

std::uint32_t Bitmap::getWidth() const {
    return infoHeader.width;
}

std::uint16_t Bitmap::getBitsPerPixel() const {
    return infoHeader.bitsPerPixel;
}

const Bitmap32BitColor &Bitmap::getColor(int index) const {
    return colorTable.getPalette().at(index);
}

std::uint8_t Bitmap::getPixel(int indexOne, int indexTwo) const {
    return pixelData.getPixels().at(indexOne).at(indexTwo);
}

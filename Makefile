CXX=g++
CXXFLAGS=-std=c++20 -pedantic -Wall
EXE=BmpParser
SDL2_CFLAGS:=$(shell sdl2-config --cflags)
SDL2_LDFLAGS:=$(shell sdl2-config --libs)

all: $(EXE)

$(EXE): BmpParser.cpp Bitmap.cpp BitmapPalette.cpp BitmapPixels.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SDL2_CFLAGS) $(SDL2_LDFLAGS)

clean:
	rm -f $(EXE)

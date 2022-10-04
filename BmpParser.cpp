#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>
#include "Bitmap.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    std::ifstream fs;
    fs.open(argv[1], std::ios::in | std::ios::binary);

    if (!fs) {
        return 1;
    }

    Bitmap bmp;

    if (bmp.readBitmap(fs)) {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *window = SDL_CreateWindow("BmpParser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        int i = bmp.getHeight() - 1;
        int j = 0;

        while (true) {
            SDL_Event event;

            if (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    break;
                }
            }

            if (i >= 0) {
                Bitmap32BitColor color = bmp.getColor(bmp.getPixel(i, j));
                SDL_SetRenderDrawColor(renderer, color.blue, color.green, color.red, 255);
                SDL_RenderDrawPoint(renderer, j + 40, ((bmp.getHeight() - 1) - i) + 40 );
                j++;

                if (j == static_cast<int>(bmp.getWidth())) {
                    i--;
                    j = 0;
                }
            }
            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    return 0;
}

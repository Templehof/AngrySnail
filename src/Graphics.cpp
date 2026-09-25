#include "Graphics.h"
#include <iostream>

SDL_Window* Graphics::window = NULL;
SDL_Renderer* Graphics::renderer = NULL;
int Graphics::windowWidth = 0;
int Graphics::windowHeight = 0;

int Graphics::Width() {
    return windowWidth;
}

int Graphics::Height() {
    return windowHeight;
}

bool Graphics::OpenWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    windowWidth = display_mode.w;
    windowHeight = display_mode.h;
    window = SDL_CreateWindow(NULL, 0, 0, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
    if (!window) {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return false;
    }
    return true;
}

SDL_Texture* Graphics::CreateCircleTexture(int size) {
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, size, size, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_LockSurface(surf);
    Uint32* px = (Uint32*)surf->pixels;
    float r = size / 2.0f;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float dx = x - r + 0.5f, dy = y - r + 0.5f;
            px[y * size + x] = (dx*dx + dy*dy <= r*r) ? 0xFFFFFFFF : 0x00000000;
        }
    SDL_UnlockSurface(surf);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    return tex;
}

void Graphics::ClearScreen(Uint32 color) {
    SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
    SDL_RenderClear(renderer);
}

void Graphics::RenderFrame() {
    SDL_RenderPresent(renderer);
}

void Graphics::DrawFillCircle(int x, int y, int radius, Uint32 color) {
    filledCircleColor(renderer, x, y, radius, color);
}

void Graphics::CloseWindow(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
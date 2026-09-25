#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Physics/Vec2.h"
#include <vector>

struct Graphics {
    static int windowWidth;
    static int windowHeight;
    static SDL_Window* window;
    static SDL_Renderer* renderer;

    static int Width();
    static int Height();
    static bool OpenWindow();

    static SDL_Texture *CreateCircleTexture(int size);

    static void CloseWindow();
    static void ClearScreen(Uint32 color);
    static void RenderFrame();
    static void DrawFillCircle(int x, int y, int radius, Uint32 color);

};
#endif
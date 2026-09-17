#include <iostream>
#include <ostream>
#include <SDL_timer.h>

#include "Application.h"
#include "Physics/Constants.h"

int main() {
    Application app;
    app.Setup();

    constexpr float DT = 1000.0f / 60.0f;
    constexpr Uint32 FRAME_MS = 1000 / 60;

    while (app.IsRunning()) {
        Uint32 frameStart = SDL_GetTicks();
        app.Input();
        app.ApplyForces();
        app.ApplyIntegration(DT);


        app.ApplyPositionalCorrection();

        Uint32 elapsed = SDL_GetTicks() - frameStart;
        if (elapsed < FRAME_MS)
            SDL_Delay(FRAME_MS - elapsed);

        app.Render();
    }


    return 0;
}

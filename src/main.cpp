#include <iostream>
#include <ostream>
#include <SDL_timer.h>

#include "Application.h"
#include "Physics/Constants.h"

int main() {
    Application app;
    app.Setup();


    Uint32 currentTime = SDL_GetTicks();

    while (app.IsRunning()) {
        Uint32 newTime = SDL_GetTicks();
        Uint32 frameStart = SDL_GetTicks();
        app.Input();
        app.ApplyForces();
        app.ApplyIntegration(16.6);

        bool hasConverged = false;
        while (!hasConverged) {
            hasConverged = app.ApplyPositionalCorrection();
            newTime = SDL_GetTicks();
        }

        Uint32 elapsed = SDL_GetTicks() - frameStart;
        if (elapsed < 16u)
            SDL_Delay(16u - elapsed);

        app.Render();
        currentTime = SDL_GetTicks();
    }


    return 0;
}

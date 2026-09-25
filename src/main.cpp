#include <iostream>
#include <ostream>
#include <SDL_timer.h>

#include "Application.h"

int main() {
    Application app;
    app.Setup();

    constexpr float DT = 1000.0f / 60.0f;
    constexpr Uint32 FRAME_MS = 1000 / 60;

    while (app.IsRunning()) {
        Uint32 frameStart = SDL_GetTicks();
        app.Input();

        auto start_time = std::chrono::high_resolution_clock::now();

        app.ApplyForces();
        app.DetectCollisions(false);
        app.ApplyVelocityIntegration(DT);
        app.ApplyContactVelocitiesResolution();

        app.ApplyPositionIntegration(DT);

        app.DetectCollisions(true);
        app.ApplyPositionalCorrection();

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> calculation_time = end_time - start_time;
        std::cout << "Physics calculations took: " << calculation_time.count() << " ms\n";

        Uint32 elapsed = SDL_GetTicks() - frameStart;
        if (elapsed < FRAME_MS)
            SDL_Delay(FRAME_MS - elapsed);

        auto start_render_time = std::chrono::high_resolution_clock::now();
        app.Render();
        auto end_render_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> calculation_render_time = end_render_time - start_render_time;
        std::cout << "Render calculations took: " << calculation_render_time.count() << " ms\n";
    }


    return 0;
}

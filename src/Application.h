#ifndef APPLICATION_H
#define APPLICATION_H
#include <SDL_rect.h>
#include <vector>

#include "SystemServices/InputProcessor.h"
#include "Physics/Particle.h"

class Application {

private:
    bool running = false;
    std::vector<Particle *> particles;
    Uint32 currentTime;

public:
    Application() = default;

    ~Application() = default;

    [[nodiscard]] bool IsRunning() const;

    void Quit();

    void Setup();

    void Input();

    void ApplyForces();

    void ApplyPositionalCorrection() const;

    void ApplyIntegration(float deltaTime) const;

    void Render();

    void Destroy() const;
};

#endif

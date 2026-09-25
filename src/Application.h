#ifndef APPLICATION_H
#define APPLICATION_H
#include <vector>

#include "Graphics.h"
#include "Physics/Boundary.h"
#include "Physics/CollisionPair.h"
#include "Physics/Particle.h"

class Application {
private:
    bool running = false;
    std::vector<Particle> particles;
    std::vector<CollisionPair> collisionPairs;
    std::vector<Boundary> boundaries;
    Uint32 currentTime;
    SDL_Texture* texture;

public:
    Application() = default;

    ~Application() = default;

    [[nodiscard]] bool IsRunning() const;

    void Quit();

    void Setup();

    void Input();

    void DetectCollisions(bool marginEnabled);

    void ApplyForces();

    void ApplyPositionalCorrection();

    void ApplyContactVelocitiesResolution();

    void ApplyVelocityIntegration(float deltaTime);
    void ApplyPositionIntegration(float deltaTime);

    void Render();

    static void Destroy();
};

#endif

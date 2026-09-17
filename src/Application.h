#ifndef APPLICATION_H
#define APPLICATION_H
#include <vector>

#include "Physics/Boundary.h"
#include "Physics/CollisionPair.h"
#include "SystemServices/InputProcessor.h"
#include "Physics/Particle.h"

class Application {
private:
    bool running = false;
    std::vector<Particle> particles;
    std::vector<CollisionPair> collisionPairs;
    std::vector<Boundary> boundaries;
    Uint32 currentTime;

public:
    Application() = default;

    ~Application() = default;

    [[nodiscard]] bool IsRunning() const;

    void Quit();

    void Setup();

    void Input();

    void ApplyForces();

    void ApplyPositionalCorrection();

    void ApplyIntegration(float deltaTime);

    void Render();

    static void Destroy();
};

#endif

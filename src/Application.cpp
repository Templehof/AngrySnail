#include "Application.h"

#include <iostream>
#include <ostream>

#include "Graphics.h"
#include "Creator/EnvironmentalForces.h"
#include "SystemServices/CollisionsObserver.h"

bool Application::IsRunning() const {
    return running;
}

void Application::Quit() {
    running = false;
}

void Application::Setup() {
    currentTime = SDL_GetTicks();
    particles.reserve(10000);
    collisionPairs.reserve(10000);
    running = Graphics::OpenWindow();

    float H = Graphics::Height();
    float W = Graphics::Width();

    boundaries = {
        {Vec2(0, -1), -H}, // floor:   y = H, interior above
        {Vec2(0, 1), 0}, // ceiling: y = 0, interior below
        {Vec2(1, 0), 0}, // left:    x = 0, interior right
        {Vec2(-1, 0), -W}, // right:   x = W, interior left
    };
}

void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        InputProcessor::processInput(particles, ([this]() {
            this->Quit();
        }), event);
    }
}

void Application::ApplyPositionalCorrection() {
    CollisionsObserver::DetectCollisionsAndApplyPositionalCorrection(particles, collisionPairs, boundaries);
}


void Application::ApplyForces() {
    EnvironmentalForces::applyGravity(particles);
    EnvironmentalForces::applyDrag(particles);
}

void Application::ApplyIntegration(float const deltaTime) {
    if (!particles.empty()) {
        auto vel = particles[0].velocity;
        std::cout << vel.Magnitude() << std::endl;
    }
    for (auto &particle: particles) {
        particle.Integrate(deltaTime);
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    for (auto &particle: particles) {
        Graphics::DrawFillCircle(particle.position.x, particle.position.y, particle.radius, 0xFFFFFFFF);
    }

    Graphics::RenderFrame();
}

void Application::Destroy() {
    Graphics::CloseWindow();
}

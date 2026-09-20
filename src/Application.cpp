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
        {Vec2(0, -1), -H}, // floor
        {Vec2(0, 1), 0}, // ceiling
        // {Vec2(1, 0), 0}, // left
        // {Vec2(-1, 0), -W}, // right
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

void Application::DetectCollisions() {
    CollisionsObserver::BuildCollisionList(particles, collisionPairs, boundaries);
}

void Application::ApplyPositionalCorrection() {
    CollisionsObserver::ApplyPositionalCorrection(particles, collisionPairs);
}

void Application::ApplyContactVelocitiesResolution() {
    CollisionsObserver::ResolveContactVelocities(particles, collisionPairs);
}


void Application::ApplyForces() {
    EnvironmentalForces::applyGravity(particles);
    EnvironmentalForces::applyDrag(particles);
}

void Application::ApplyIntegration(float const deltaTime) {
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

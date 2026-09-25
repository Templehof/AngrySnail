#include "Application.h"
#include "Graphics.h"
#include "Creator/EnvironmentalForces.h"
#include "SystemServices/CollisionsObserver.h"
#include <chrono>

#include "SystemServices/InputProcessor.h"

bool Application::IsRunning() const {
    return running;
}

void Application::Quit() {
    running = false;
}

void Application::Setup() {
    currentTime = SDL_GetTicks();
    particles.reserve(100000);
    collisionPairs.reserve(10000);
    running = Graphics::OpenWindow();
    texture = Graphics::CreateCircleTexture(10);

    float H = Graphics::Height();
    float W = Graphics::Width();

    boundaries = {
        {Vec2(0, -1), -H}, // floor
        {Vec2(1, 0), 0}, // left
        {Vec2(-1, 0), -W}, // right
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

void Application::DetectCollisions(bool marginEnabled) {
    CollisionsObserver::BuildCollisionList(particles, collisionPairs, boundaries, marginEnabled);
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

void Application::ApplyVelocityIntegration(float const deltaTime) {
    for (auto &particle: particles) {
        particle.IntegrateVelocity(deltaTime);
    }
}

void Application::ApplyPositionIntegration(float deltaTime) {
    for (auto &particle: particles) {
        particle.IntegratePosition(deltaTime);
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    // if (!particles.empty()) {
    //     for (int i = 0; i < particles.size(); ++i) {
    //         std::cout << particles[i].velocity.y << std::endl;
    //     }
    // }


    for (auto &particle: particles) {
        SDL_FRect dst = {
            particle.position.x - particle.radius,
            particle.position.y - particle.radius,
            particle.radius * 2.0f,
            particle.radius * 2.0f
        };
        SDL_RenderCopyF(Graphics::renderer, texture, nullptr, &dst);
    }

    Graphics::RenderFrame();
}

void Application::Destroy() {
    Graphics::CloseWindow();
}

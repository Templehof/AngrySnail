#include "Application.h"
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
    particles.reserve(1000);
    running = Graphics::OpenWindow();
}

void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        InputProcessor::processInput(particles, ([this]() {
            this->Quit();
        }), event);
    }
}

void Application::ApplyPositionalCorrection() const {
    CollisionsObserver::DetectCollisionsAndApplyPositionalCorrection(particles);
    CollisionsObserver::ResolveBoundaryCollisions(particles, Graphics::windowWidth, Graphics::windowHeight);
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

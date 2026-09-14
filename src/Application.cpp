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
    particles = std::vector<Particle *>();
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

void Application::ApplyIntegration(float deltaTime) const {
    for (auto particle_: particles) {
        particle_->Integrate(deltaTime);
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    for (auto particle_: particles) {
        Graphics::DrawFillCircle(particle_->position.x, particle_->position.y, particle_->radius, 0xFFFFFFFF);
    }

    Graphics::RenderFrame();
}

void Application::Destroy() const {
    for (const auto &particle: particles) {
        delete particle;
    }
    Graphics::CloseWindow();
}

//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "../SystemServices//InputProcessor.h"

#include <functional>
#include <SDL_events.h>
#include <vector>

#include "../Creator/Actions.h"
#include "../Physics/Particle.h"

void InputProcessor::processInput(std::vector<Particle *> &particles, const std::function<void()> &quitCallBack,
                                  const SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT:
            quitCallBack();
            break; // Added

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitCallBack();
            }
            break; // Added

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP) {
                Actions::pushAllUp(particles);
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                Actions::pushAllDown(particles);
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                Actions::pushAllRight(particles);
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                Actions::pushAllLeft(particles);
            }
            break; // Added

        case SDL_MOUSEBUTTONDOWN:
            Actions::shootParticle(particles, event.button.x, event.button.y);
            break; // Added
        default: break;
    }
}

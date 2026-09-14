//
// Created by Ivan Riumkin on 2026-09-11.
//

#ifndef ANGRYSNAIL_INPUTPROCESSOR_H
#define ANGRYSNAIL_INPUTPROCESSOR_H
#include <SDL_events.h>
#include <vector>
#include <__functional/function.h>

#include "../Physics/Particle.h"


namespace InputProcessor {
    void processInput(std::vector<Particle *> &particles, const std::function<void()> &quitCallBack, const SDL_Event &event);
};


#endif //ANGRYSNAIL_INPUTPROCESSOR_H

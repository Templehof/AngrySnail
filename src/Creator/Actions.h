//
// Created by Ivan Riumkin on 2026-09-11.
//

#ifndef ANGRYSNAIL_ACTIONS_H
#define ANGRYSNAIL_ACTIONS_H
#include <vector>

#include "../Physics/Particle.h"


namespace Actions {
    void pushAllLeft(std::vector<Particle *> &particles);
    void pushAllRight(std::vector<Particle *> &particles);
    void pushAllUp(std::vector<Particle *> &particles);
    void pushAllDown(std::vector<Particle *> &particles);
    void spawnParticle(std::vector<Particle *> &particles, float x, float y);
    void shootParticle(std::vector<Particle *> &particles, float x, float y);
}

#endif //ANGRYSNAIL_ACTIONS_H

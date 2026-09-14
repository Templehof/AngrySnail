//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "EnvironmentalForces.h"

#include "../Physics/Constants.h"
#include "../Physics/Force.h"


void EnvironmentalForces::applyGravity(std::vector<Particle *> &particles) {
    for (auto _p: particles) {
        auto gForce = Force::GenerateGravity(*_p);
        _p->AddForce(gForce);
    }
}

void EnvironmentalForces::applyDrag(std::vector<Particle *> &particles) {
    for (auto _p: particles) {
        float speed = _p->velocity.Magnitude();
        Vec2 dragForce;
        dragForce = _p->velocity * (-0.1f * speed);
        auto dragAcceleration = dragForce / _p->mass;
        _p->AddForce(dragAcceleration);
    }
}

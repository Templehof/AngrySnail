//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "EnvironmentalForces.h"
#include "../Physics/Force.h"


void EnvironmentalForces::applyGravity(std::vector<Particle> &particles) {
    for (auto &p: particles) {
        auto gForce = Force::GenerateGravity(p);
        p.AddForce(gForce);
    }
}

void EnvironmentalForces::applyDrag(std::vector<Particle> &particles) {
    for (auto &p: particles) {
        float speed = p.velocity.Magnitude();
        Vec2 dragForce;
        dragForce = p.velocity * (-0.1f * speed);
        auto dragAcceleration = dragForce / p.mass;
        p.AddForce(dragAcceleration);
    }
}

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
        Vec2 dragForce = p.velocity * (-0.2f * p.velocity.Magnitude());
        auto dragAcceleration = dragForce * p.invMass;
        p.AddForce(dragAcceleration);
    }
}

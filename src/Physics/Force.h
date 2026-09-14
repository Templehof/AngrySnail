//
// Created by Ivan Riumkin on 2026-08-17.
//

#ifndef ANGRYSNAIL_FORCE_H
#define ANGRYSNAIL_FORCE_H
#include "Particle.h"
#include "Vec2.h"

struct Force {
    static Vec2 GenerateDragForce(const Particle &particle, float k);

    static Vec2 GenerateFrictionForcesParticles(const Particle &particleA, const Particle &particleB, float k, float normalForce);

    static Vec2 GenerateFrictionForceHorizontal(const Particle &particle, float k);

    static Vec2 GenerateGravity(const Particle &a);

    static Vec2 GenerateGravitationalForce(const Particle &a, const Particle &b, float G);

    static Vec2 GenerateSpringForce(const Particle &particle, Vec2 anchor, float restLength, float k);
};

#endif //ANGRYSNAIL_FORCE_H

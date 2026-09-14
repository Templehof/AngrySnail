//
// Created by Ivan Riumkin on 2026-08-14.
//

#ifndef ANGRYSNAIL_PARTICLE_H
#define ANGRYSNAIL_PARTICLE_H
#include "Vec2.h"

struct Particle {
    Vec2 prevPosition;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    Vec2 sumForces;

    float radius;
    float radiusSquared;
    float mass;
    float invMass;

    Particle(float x, float y, float mass, float radius);

    ~Particle();

    void Integrate(float dt);

    void AddForce(const Vec2 &force);

    void ClearForces();

    void UpdatePosition(const Vec2 &newPosition);
};

#endif //ANGRYSNAIL_PARTICLE_H

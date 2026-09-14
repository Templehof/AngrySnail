//
// Created by Ivan Riumkin on 2026-08-14.
//

#include "Particle.h"

Particle::Particle(float x, float y, float mass, float radius) {
    this->position = Vec2(x, y);
    this->prevPosition = Vec2(x, y);
    this->mass = mass;
    if (mass != 0.0) {
        this->invMass = 1.0f / mass;
    } else {
        this->invMass = 0.0;
    }
    this->radius = radius;
    this->radiusSquared = radius * radius;
}

Particle::~Particle() {
}

void Particle::UpdatePosition(const Vec2 &newPosition) {
    this->position = newPosition;
}

void Particle::AddForce(const Vec2 &force) {
    sumForces += force;
}

void Particle::ClearForces() {
    sumForces = Vec2(0.0, 0.0);
}

void Particle::Integrate(const float dtMillis) {
    float dtSeconds = dtMillis / 1000.0f;
    acceleration = sumForces * invMass;
    velocity += acceleration * dtSeconds;
    UpdatePosition(position + velocity * dtSeconds);
    ClearForces();
}

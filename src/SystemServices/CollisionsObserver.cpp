//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "CollisionsObserver.h"

#include <iostream>
#include <ostream>

#include "../Physics/CollisionPair.h"
#include "../Physics/CollisionResolver.h"
#include "../Physics/Force.h"

void CollisionsObserver::DetectCollisionsAndResolveKineticCollision(std::vector<Particle> &particles) {
    if (particles.empty()) {
        return;
    }

    for (int i = 0; i < particles.size() - 1; i++) {
        for (int j = i + 1; j < particles.size(); j++) {
            if (IsColliding(particles[i], particles[j])) {
                CollisionResolver::ResolveKineticCollision(particles[i], particles[j]);
            }
        }
    }
}

void CollisionsObserver::DetectCollisionsAndApplyPositionalCorrection(std::vector<Particle> &particles) {
    if (particles.empty()) {
        return;
    }

    std::vector<CollisionPair> collision_pairs;

    for (int i = 0; i < particles.size() - 1; i++) {
        for (int j = i + 1; j < particles.size(); j++) {
            BuildCollisionList(particles[i], i, particles[j], j, collision_pairs);
        }
    }
}

bool CollisionsObserver::IsColliding(Particle &a, Particle &b) {
    float distanceSquared = (a.position.x - b.position.x) * (a.position.x - b.position.x) + (
                                a.position.y - b.position.y) * (a.position.y - b.position.y);

    return distanceSquared <= (a.radius + b.radius) * (a.radius + b.radius);
}

void CollisionsObserver::BuildCollisionList(Particle &a, int aIndex, Particle &b, int bIndex,
                                            std::vector<CollisionPair> &overlappedParticles) {
    float distanceSquared = (a.position.x - b.position.x) * (a.position.x - b.position.x) + (
                                a.position.y - b.position.y) * (a.position.y - b.position.y);

    float overlap = (a.radius + b.radius) * (a.radius + b.radius) - distanceSquared;

    if (overlap > 0.01f) {
        overlappedParticles.push_back(CollisionPair(aIndex, bIndex, overlap));
    }
}

void CollisionsObserver::ResolveBoundaryCollisions(std::vector<Particle> &particles, int screenWidth,
                                                   int screenHeight) {
    const float restitution = 0.2f;
    for (auto &p: particles) {
        Vec2 frictionForce = Force::GenerateFrictionForceHorizontal(p, 0.9);

        if (p.position.x - p.radius <= 0) {
            p.position.x = p.radius;
            p.velocity.x = std::abs(p.velocity.x) * restitution;
        }
        // 2. Right Boundary (X = screenWidth)
        else if (p.position.x + p.radius >= screenWidth) {
            p.position.x = screenWidth - p.radius;
            p.velocity.x = -std::abs(p.velocity.x) * restitution;
        }

        // 3. Top Boundary (Y = 0)
        if (p.position.y - p.radius <= 0) {
            p.position.y = p.radius;
            p.velocity.y = std::abs(p.velocity.y) * restitution;

            // p.AddForce(frictionForce);
        }

        // 4. Bottom Boundary (Y = screenHeight)
        else if (p.position.y + p.radius >= screenHeight) {
            p.position.y = screenHeight - p.radius;
            p.velocity.y = -std::abs(p.velocity.y) * restitution;
            p.velocity.x += frictionForce.x;
        }
    }
}

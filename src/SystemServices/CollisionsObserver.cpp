//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "CollisionsObserver.h"

#include <iostream>
#include <ostream>

#include "../Physics/Boundary.h"
#include "../Physics/CollisionPair.h"
#include "../Physics/CollisionResolver.h"
#include "../Physics/Constants.h"
#include "../Physics/Force.h"

void CollisionsObserver::DetectCollisionsAndResolveKineticCollision(std::vector<Particle> &particles) {
    if (particles.empty()) {
        return;
    }

    // for (int i = 0; i < particles.size() - 1; i++) {
    //     for (int j = i + 1; j < particles.size(); j++) {
    //         // if (IsColliding(particles[i], particles[j])) {
    //         //     CollisionResolver::ResolveKineticCollision(particles[i], particles[j]);
    //         // }
    //     }
    // }
}

void CollisionsObserver::DetectCollisionsAndApplyPositionalCorrection(std::vector<Particle> &particles,
                                                                      std::vector<CollisionPair> &collision_pairs,
                                                                      std::vector<Boundary> &boundaries) {
    collision_pairs.clear();
    if (particles.empty()) {
        return;
    }

    for (int i = 0; i < particles.size() - 1; i++) {
        for (int j = i + 1; j < particles.size(); j++) {
            BuildCollisionList(particles[i], i, particles[j], j, collision_pairs);
        }
    }

    for (int i = 0; i < particles.size(); i++)
        for (auto &b: boundaries)
            if (b.depth(particles[i]) > -POS_MARGIN)
                collision_pairs.push_back({i, -1, b.normal, b.c});


    int iter = 0;
    float maxErr;
    do {
        maxErr = 0;
        for (auto &c: collision_pairs)
            CorrectPositions(particles, c, maxErr);
    } while (maxErr > POS_CORR_SLOP && ++iter < POS_CORR_ITER);
}

void CollisionsObserver::BuildCollisionList(Particle &a, int aIndex, Particle &b, int bIndex,
                                            std::vector<CollisionPair> &overlappedParticles) {
    float distanceSquared = (a.position - b.position).Magnitude();

    float overlap = (a.radius + b.radius) - distanceSquared + POS_MARGIN;

    if (overlap >= POS_CORR_SLOP) {
        overlappedParticles.push_back(CollisionPair(aIndex, bIndex));
    }
}

void CollisionsObserver::
CorrectPositions(std::vector<Particle> &particles, CollisionPair &cp, float &maxErr) {
    Particle &A = particles[cp.aIndex];
    if (cp.bIndex > -1) {
        Particle &B = particles[cp.bIndex];
        Vec2 posDelta = B.position - A.position;

        float dist = posDelta.Magnitude();
        float penDepth = (A.radius + B.radius) - dist;

        if (penDepth <= POS_CORR_SLOP) {
            return;
        }

        Vec2 contactNormal;

        if (dist < 1e-6f) {
            contactNormal = Vec2(1, 0);
        } else {
            contactNormal = posDelta.UnitVector();
        }

        float corr = (penDepth - POS_CORR_SLOP) * POS_CORR_PERCENTAGE;

        float wa = A.invMass, wb = B.invMass;
        float wsum = wa + wb;

        if (wsum == 0.0f) return;

        A.position -= contactNormal * corr * (wa / wsum);
        B.position += contactNormal * corr * (wb / wsum);

        // Vec2 approachingVelocity = Vec2(0, 0);
        // A.velocity = approachingVelocity;
        // B.velocity = approachingVelocity;
        maxErr = std::max(maxErr, corr);

    } else {
        float depth = A.radius - (A.position.Dot(cp.planeNormal) - cp.planeC);
        if (depth <= POS_CORR_SLOP) return;

        float corr = (depth - POS_CORR_SLOP) * POS_CORR_PERCENTAGE;
        A.position += cp.planeNormal * corr;

        // Vec2 approachingVelocity = A.velocity;
        // A.velocity -= approachingVelocity;
        maxErr = std::max(maxErr, corr);
    }
}

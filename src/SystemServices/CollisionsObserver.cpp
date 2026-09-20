//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "CollisionsObserver.h"

#include <iostream>
#include <ostream>

#include "../Physics/Boundary.h"
#include "../Physics/CollisionPair.h"
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

void CollisionsObserver::ApplyPositionalCorrection(std::vector<Particle> &particles,
                                                   std::vector<CollisionPair> &collision_pairs) {
    int iter = 0;
    float maxErr;
    do {
        maxErr = 0;
        for (auto &c: collision_pairs)
            CorrectPositions(particles, c, maxErr);
    } while (maxErr > POS_CORR_SLOP && ++iter < POS_CORR_ITER);
}

void CollisionsObserver::BuildCollisionList(std::vector<Particle> &particles,
                                            std::vector<CollisionPair> &collision_pairs,
                                            std::vector<Boundary> &boundaries) {
    collision_pairs.clear();
    if (particles.empty()) {
        return;
    }

    for (int i = 0; i < particles.size() - 1; i++) {
        for (int j = i + 1; j < particles.size(); j++) {
            Particle &a = particles[i];
            Particle &b = particles[j];
            float distanceSquared = (a.position - b.position).Magnitude();
            float overlap = (a.radius + b.radius) - distanceSquared + POS_MARGIN;

            if (overlap > POS_CORR_SLOP) {
                collision_pairs.push_back(CollisionPair(i, j));
            }
        }
    }

    for (int i = 0; i < particles.size(); i++) {
        for (auto &b: boundaries) {
            float penDept = b.depth(particles[i]);
            if (penDept < -POS_CORR_SLOP) {
                collision_pairs.push_back({i, -1, b.normal, b.c});
            }
        }
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
        maxErr = std::max(maxErr, corr);
    } else {
        float depth = A.radius - (A.position.Dot(cp.planeNormal) - cp.planeC);
        if (depth <= POS_CORR_SLOP) return;
        float corr = (depth - POS_CORR_SLOP) * POS_CORR_PERCENTAGE;
        A.position += cp.planeNormal * corr;
        maxErr = std::max(maxErr, corr);
    }
}

void CollisionsObserver::ResolveContactVelocities(std::vector<Particle> &particles,
                                                  const std::vector<CollisionPair> &collision_pairs) {
    for (int i = 0; i < REST_VELOCITY_RESOLUTION_ITER; ++i) {
        for (auto &cp: collision_pairs) {
            if (cp.bIndex != -1) {
                Particle &a = particles[cp.aIndex];
                Particle &b = particles[cp.bIndex];

                Vec2 velocityDelta = a.velocity - b.velocity;
                Vec2 contactNormal = velocityDelta.UnitVector();

                float wsum = a.invMass + b.invMass;
                float closingVelocity = velocityDelta.Dot(contactNormal);

                if (closingVelocity < 0) {
                    continue;
                }

                float J = -closingVelocity / wsum;
                a.velocity += contactNormal * (J * a.invMass);
                b.velocity -= contactNormal * (J * b.invMass);
            } else {
                Particle &a = particles[cp.aIndex];
                float closingVelocity = a.velocity.Dot(cp.planeNormal);

                if (closingVelocity > 0) {
                    continue;
                }

                Vec2 closingVelocityVector = cp.planeNormal * closingVelocity;
                a.velocity -= closingVelocityVector;
            }
        }
    }
}

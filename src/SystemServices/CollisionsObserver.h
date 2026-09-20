//
// Created by Ivan Riumkin on 2026-09-11.
//

#ifndef ANGRYSNAIL_COLLISIONSOBSERVER_H
#define ANGRYSNAIL_COLLISIONSOBSERVER_H
#include <vector>

#include "../Physics/Boundary.h"
#include "../Physics/CollisionPair.h"
#include "../Physics/Particle.h"


namespace CollisionsObserver {
    void DetectCollisionsAndResolveKineticCollision(std::vector<Particle> &particles);

    void ApplyPositionalCorrection(std::vector<Particle> &particles,
                                   std::vector<CollisionPair> &collision_pairs);

    void CorrectPositions(std::vector<Particle> &particles, CollisionPair &cp, float &maxErr);

    void ResolveContactVelocities(std::vector<Particle> &particles, const std::vector<CollisionPair> &collision_pairs);

    void BuildCollisionList(std::vector<Particle> &particles,
                            std::vector<CollisionPair> &collision_pairs,
                            std::vector<Boundary> &boundaries, bool marginEnabled);
}


#endif //ANGRYSNAIL_COLLISIONSOBSERVER_H

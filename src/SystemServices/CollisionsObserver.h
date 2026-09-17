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

    void DetectCollisionsAndApplyPositionalCorrection(std::vector<Particle> &particles,
                                                      std::vector<CollisionPair> &collision_pairs,
                                                      std::vector<Boundary> &boundaries);

    void CorrectPositions(std::vector<Particle> &particles, CollisionPair &cp, float &maxErr);

    void BuildCollisionList(Particle &a, int aIndex, Particle &b, int bIndex,
                            std::vector<CollisionPair> &overlappedParticles);
}


#endif //ANGRYSNAIL_COLLISIONSOBSERVER_H

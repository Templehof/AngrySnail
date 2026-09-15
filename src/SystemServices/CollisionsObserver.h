//
// Created by Ivan Riumkin on 2026-09-11.
//

#ifndef ANGRYSNAIL_COLLISIONSOBSERVER_H
#define ANGRYSNAIL_COLLISIONSOBSERVER_H
#include <vector>

#include "../Physics/CollisionPair.h"
#include "../Physics/Particle.h"


namespace CollisionsObserver {
    void DetectCollisionsAndResolveKineticCollision(std::vector<Particle> &particles);

    void DetectCollisionsAndApplyPositionalCorrection(std::vector<Particle> &particles);

    void ResolveBoundaryCollisions(std::vector<Particle> &particles, int screenWidth, int screenHeight);

    bool IsColliding(Particle &a, Particle &b);

    void BuildCollisionList(Particle &a, int aIndex, Particle &b, int bIndex,
                            std::vector<CollisionPair> &overlappedParticles);
}


#endif //ANGRYSNAIL_COLLISIONSOBSERVER_H

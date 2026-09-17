//
// Created by Ivan Riumkin on 2026-09-14.
//

#ifndef ANGRYSNAIL_COLLISIONPAIR_H
#define ANGRYSNAIL_COLLISIONPAIR_H
#include "Vec2.h"

struct CollisionPair {
    int aIndex;
    int bIndex;

    Vec2 planeNormal; // boundary only: unit, points INTO the playable area
    float planeC; // boundary only: plane equation dot(x, planeNormal) = planeC
};


#endif //ANGRYSNAIL_COLLISIONPAIR_H

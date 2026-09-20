//
// Created by Ivan Riumkin on 2026-09-17.
//

#ifndef ANGRYSNAIL_BOUNDARY_H
#define ANGRYSNAIL_BOUNDARY_H
#include <iostream>

#include "Particle.h"
#include "Vec2.h"

struct Boundary {
    Vec2 normal;
    float c; // signed distance from the origin to the boundary line

    // signed distance from plane to particle surface (positive = clear, negative = penetrating)
    [[nodiscard]] float depth(const Particle &p) const {
        float d = p.position.Dot(normal) - c - p.radius;
        return d;
    }
};

#endif //ANGRYSNAIL_BOUNDARY_H

//
// Created by Ivan Riumkin on 2026-09-17.
//

#ifndef ANGRYSNAIL_BOUNDARY_H
#define ANGRYSNAIL_BOUNDARY_H
#include "Particle.h"
#include "Vec2.h"

struct Boundary {
    Vec2 normal;
    float c; // plane equation: dot(x, normal) = c signed distance from the origin to the boundary line

    // signed distance from plane to particle surface (positive = clear, negative = penetrating)
    [[nodiscard]] float depth(const Particle &p) const {
        return p.position.Dot(p.position.Normal()) - c - p.radius;
    }
};

#endif //ANGRYSNAIL_BOUNDARY_H

//
// Created by Ivan Riumkin on 2026-08-17.
//

#include "Force.h"

#include "Constants.h"
#include "Vec2.h"
#include <cmath>

Vec2 Force::GenerateDragForce(const Particle &particle, const float k) {
    Vec2 dragForce = Vec2(0, 0);
    if (particle.velocity.SquaredMagnitude() > 0) {
        const Vec2 dragDirection = particle.velocity.UnitVector() * -1.0;
        const float dragMagnitude = k * particle.velocity.SquaredMagnitude();
        dragForce = dragDirection * dragMagnitude;
    }
    return dragForce;
}

Vec2 Force::GenerateFrictionForcesParticles(const Particle &particleA, const Particle &particleB, const float k,
                                            const float normalForce) {
    // 1. Calculate the collision normal vector (direction from B to A)
    Vec2 normal = particleA.position - particleB.position;
    float distance = normal.Magnitude();

    // Prevent division by zero if particles are exactly overlapping
    if (distance < 0.0001f) {
        return Vec2(0.0f, 0.0f);
    }

    normal = normal.UnitVector();

    Vec2 relativeVelocity = particleA.velocity - particleB.velocity;

    // 3. Project relative velocity onto the normal to find the bounce speed
    float speedAlongNormal = relativeVelocity.Dot(normal);

    // 4. Subtract the normal velocity from the total relative velocity
    // to isolate the tangential (sliding) velocity
    Vec2 normalVelocity = normal;
    normalVelocity.Scale(speedAlongNormal);

    Vec2 tangentVelocity = relativeVelocity - normalVelocity;
    float tangentSpeed = tangentVelocity.Magnitude();

    // 5. If they aren't sliding against each other, there is no kinetic friction
    if (tangentSpeed < 0.001f) {
        return Vec2(0.0f, 0.0f);
    }

    // 6. Calculate final friction force
    Vec2 frictionDirection = tangentVelocity;
    frictionDirection.Scale(1.0f / tangentSpeed); // Normalize

    float frictionMagnitude = k * std::abs(normalForce);

    // Friction force on A opposes its sliding direction relative to B
    frictionDirection.Scale(-frictionMagnitude);

    return frictionDirection;
}

Vec2 Force::GenerateFrictionForceHorizontal(const Particle &particle, const float k) {
    float speed = particle.velocity.Magnitude();
    float normalForce = particle.mass * GRAVITY_CONSTANT;

    // 1. Static Friction
    if (speed < 0.01f) {
        float maxStaticFriction = k * normalForce;
        Vec2 externalForce = particle.sumForces;

        // If the horizontal push is weaker than stiction, cancel it out perfectly
        if (std::abs(externalForce.x) <= maxStaticFriction) {
            return Vec2(-externalForce.x, 0.0f);
        }

        float pushDirection = (externalForce.x > 0.0f) ? 1.0f : -1.0f;
        return Vec2(-pushDirection * (k * normalForce), 0.0f);
    }

    float frictionForceMagnitude = k * normalForce;
    Vec2 Vn = particle.velocity.UnitVector();
    Vn.Scale(-frictionForceMagnitude);
    return Vn;
}

Vec2 Force::GenerateGravity(const Particle &a) {
    return {0, a.mass * GRAVITY_CONSTANT};
}

Vec2 Force::GenerateGravitationalForce(const Particle &a, const Particle &b, float G) {
    Vec2 d = (b.position - a.position);
    float distanceSquared = d.SquaredMagnitude();
    Vec2 attractionDirection = d.UnitVector();
    float attractionMagnitude = G * (a.mass * b.mass) / distanceSquared;
    Vec2 attractionForce = attractionDirection * attractionMagnitude;
    return attractionForce;
}

Vec2 Force::GenerateSpringForce(const Particle &particle, Vec2 anchor, float restLength, float k) {
    Vec2 d = particle.position - anchor;
    float displacement = d.Magnitude() - restLength;
    Vec2 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;
    Vec2 springForce = springDirection * springMagnitude;
    return springForce;
}

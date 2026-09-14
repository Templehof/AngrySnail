//
// Created by Ivan Riumkin on 2026-09-12.
//

#include "CollisionResolver.h"

#include <algorithm>

#include "Force.h"

#include <algorithm> // for std::max and std::min

void CollisionResolver::ResolveKineticCollision(Particle *a, Particle *b) {
    float maInverse = a->invMass;
    float mbInverse = b->invMass;

    Vec2 velA = a->velocity;
    Vec2 velB = b->velocity;

    Vec2 posA = a->position;
    Vec2 posB = b->position;

    const float restitutionCoefficient = 0.2f;
    const float frictionCoefficient = 0.3f;

    Vec2 collisionNormal = (posA - posB).UnitVector();
    Vec2 relativeVelocity = (velA - velB);
    float closingVelocity = relativeVelocity.Dot(collisionNormal);

    float e = (closingVelocity < -1.0f) ? restitutionCoefficient : 0.0f;

    // Only resolve if they are moving toward each other
    if (closingVelocity < 0.0f) {
        float impulseScalar = -(1 + e) * closingVelocity / (maInverse + mbInverse);

        Vec2 scaledNormalA = collisionNormal;
        scaledNormalA.Scale(impulseScalar * maInverse);

        Vec2 scaledNormalB = collisionNormal;
        scaledNormalB.Scale(impulseScalar * mbInverse);

        a->velocity += scaledNormalA;
        b->velocity -= scaledNormalB;

        Vec2 normalVelocity = collisionNormal;
        normalVelocity.Scale(closingVelocity);

        Vec2 tangent = relativeVelocity;
        tangent -= normalVelocity;

        float tangentMagnitude = tangent.Magnitude();

        // Static sliding
        if (tangentMagnitude > 0.0001f) {
            tangent = tangent.UnitVector();

            float tangentVelocity = relativeVelocity.Dot(tangent);
            float frictionImpulseScalar = -tangentVelocity / (maInverse + mbInverse);

            // Coulomb's Law: Friction impulse cannot exceed mu * normalImpulse
            float maxFriction = frictionCoefficient * impulseScalar;

            // Clamp the friction impulse
            frictionImpulseScalar = std::max(-maxFriction, std::min(maxFriction, frictionImpulseScalar));

            // Apply the friction impulse
            Vec2 frictionImpulseA = tangent;
            frictionImpulseA.Scale(frictionImpulseScalar * maInverse);

            Vec2 frictionImpulseB = tangent;
            frictionImpulseB.Scale(frictionImpulseScalar * mbInverse);

            a->velocity += frictionImpulseA;
            b->velocity -= frictionImpulseB;
        }
    }
}

#include <algorithm>

bool CollisionResolver::applyPositionalCorrection(Particle *a, Particle *b) {
    float maInverse = a->invMass;
    float mbInverse = b->invMass;
    float invMassSum = maInverse + mbInverse;

    if (invMassSum == 0.0f) return true;

    Vec2 distanceVector = a->position - b->position;
    float distance = distanceVector.Magnitude();

    float penetration = (a->radius + b->radius) - distance;
    Vec2 normal;

    if (distance < 0.0001f) {
        normal = Vec2(0.0f, 1.0f);
    } else {
        normal = distanceVector * (1.0f / distance);
    }

    float correctionScalar = (penetration);

    Vec2 correction = normal * (correctionScalar / invMassSum);

    auto finalPositionA = a->position + correction * maInverse;
    auto finalPositionB = b->position - correction * mbInverse;

    bool positionsChanged = (finalPositionA.Magnitude() - a->position.Magnitude() + finalPositionB.Magnitude() - b->
                             position.Magnitude()) > 1.0f;

    a->UpdatePosition(finalPositionA);
    b->UpdatePosition(finalPositionB);

    return positionsChanged;
}

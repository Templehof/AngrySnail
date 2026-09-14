//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "Actions.h"

#include "../Physics/Constants.h"

void Actions::pushAllLeft(std::vector<Particle *> &particles) {
    Vec2 leftPush = Vec2(-1000, 0);
    for (Particle *part: particles) {
        part->AddForce(leftPush);
    }
}

void Actions::pushAllRight(std::vector<Particle *> &particles) {
    Vec2 rightPush = Vec2(10000, 0);
    for (Particle *part: particles) {
        part->AddForce(rightPush);
    }
}

void Actions::pushAllUp(std::vector<Particle *> &particles) {
    Vec2 upPush = Vec2(0, 1000);
    for (Particle *part: particles) {
        part->AddForce(upPush);
    }
}

void Actions::pushAllDown(std::vector<Particle *> &particles) {
    Vec2 downPush = Vec2(0, 1000);
    for (Particle *part: particles) {
        part->AddForce(downPush);
    }
}

void Actions::spawnParticle(std::vector<Particle *> &particles, float x, float y) {
    particles.push_back(new Particle(x, y, 10, 20));
}

void Actions::shootParticle(std::vector<Particle *> &particles, float x, float y) {
    // for (int i = 0; i < 100; i++) {
    //     auto *spawnedParticle = new Particle(x, y, 10, 10);
    //     spawnedParticle->velocity.Add(Vec2(i, 0));
    //     particles.push_back(spawnedParticle);
    // }
    auto *spawnedParticle = new Particle(x, y, 10, 10);
    spawnedParticle->velocity.Add(Vec2(0, 0));
    particles.push_back(spawnedParticle);
}

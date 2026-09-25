//
// Created by Ivan Riumkin on 2026-09-11.
//

#include "Actions.h"

void Actions::pushAllLeft(std::vector<Particle> &particles) {
    Vec2 leftPush = Vec2(-10000, 0);
    for (auto &p: particles) {
        p.AddForce(leftPush);
    }
}

void Actions::pushAllRight(std::vector<Particle> &particles) {
    Vec2 rightPush = Vec2(100000, 0);
    for (auto &p: particles) {
        p.AddForce(rightPush);
    }
}

void Actions::pushAllUp(std::vector<Particle> &particles) {
    Vec2 upPush = Vec2(0, 10000);
    for (auto &p: particles) {
        p.AddForce(upPush);
    }
}

void Actions::pushAllDown(std::vector<Particle> &particles) {
    Vec2 downPush = Vec2(0, 10000);
    for (auto &p: particles) {
        p.AddForce(downPush);
    }
}

void Actions::spawnParticle(std::vector<Particle> &particles, float x, float y) {
    particles.emplace_back(x, y, 10, 20);
}

void Actions::shootParticle(std::vector<Particle> &particles, float x, float y) {
    for (int i = 0; i < 1; ++i) {
        Particle tempParticle(x + i * 10, y, 10, 20);
        tempParticle.velocity.Add(Vec2(0, 0));
        particles.emplace_back(tempParticle);
    }
}

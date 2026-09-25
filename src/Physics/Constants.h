//
// Created by Ivan Riumkin on 2026-08-14.
//

#ifndef ANGRYSNAIL_CONSTANTS_H
#define ANGRYSNAIL_CONSTANTS_H

constexpr float GRAVITY_CONSTANT = 9.8f * 100;

constexpr float POS_CORR_SLOP = 0.2f;
constexpr float POS_CORR_PERCENTAGE = 0.8f;
constexpr float POS_MARGIN = 0;

constexpr int POS_CORR_ITER = 20;

constexpr int REST_VELOCITY_RESOLUTION_ITER = 20;
#endif //ANGRYSNAIL_CONSTANTS_H

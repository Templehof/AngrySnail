//
// Created by Ivan Riumkin on 2026-08-14.
//

#ifndef ANGRYSNAIL_CONSTANTS_H
#define ANGRYSNAIL_CONSTANTS_H
#include <SDL_stdinc.h>

constexpr float GRAVITY_CONSTANT = 9.8f * 100;

constexpr float POS_CORR_SLOP = 0.02f;
constexpr float POS_CORR_PERCENTAGE = 0.8f;
constexpr float POS_MARGIN = 10;

constexpr int POS_CORR_ITER = 20;

constexpr int REST_VELOCITY_RESOLUTION_ITER = 4;
#endif //ANGRYSNAIL_CONSTANTS_H

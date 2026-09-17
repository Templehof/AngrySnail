//
// Created by Ivan Riumkin on 2026-08-14.
//

#ifndef ANGRYSNAIL_CONSTANTS_H
#define ANGRYSNAIL_CONSTANTS_H
#include <SDL_stdinc.h>

constexpr float GRAVITY_CONSTANT = 9.8f;
constexpr int PIXELS_PER_METER = 100;

constexpr float FIXED_TIME_DELTA = 0.1f;

constexpr Uint32 MILLISECONDS_PER_FRAME = 16u;

constexpr float POS_CORR_SLOP = 0.0f;
constexpr float POS_CORR_PERCENTAGE = 1.0f;
constexpr int POS_CORR_ITER = 100;
constexpr float POS_MARGIN = 20;
#endif //ANGRYSNAIL_CONSTANTS_H

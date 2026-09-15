//
// Created by Ivan Riumkin on 2026-09-11.
//

#ifndef ANGRYSNAIL_ENVIRONMENTALFORCES_H
#define ANGRYSNAIL_ENVIRONMENTALFORCES_H
#include <vector>

#include "../Physics/Particle.h"


namespace EnvironmentalForces {
    void applyGravity(std::vector<Particle> &particles);

    void applyDrag(std::vector<Particle> &particles);
};


#endif //ANGRYSNAIL_ENVIRONMENTALFORCES_H

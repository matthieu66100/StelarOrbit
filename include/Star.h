#ifndef SOLARSYSTEM_STAR_H
#define SOLARSYSTEM_STAR_H

#include "CelestialBody.h"

class Star : public CelestialBody {
public:
    Star(float x, float y, float radius);
    void update(float deltaTime) override;
};

#endif // SOLARSYSTEM_STAR_H



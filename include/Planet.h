#ifndef SOLARSYSTEM_PLANET_H
#define SOLARSYSTEM_PLANET_H

#include "CelestialBody.h"
#include "Star.h"

class Planet : public CelestialBody {
private:
    Star* parentStar;
    float orbitRadius;
    float orbitAngle;
    float orbitSpeed;

public:
    Planet(Star* star, float distance, float radius, sf::Color color, const std::string& name, float speed);
    void update(float deltaTime) override;
};

#endif // SOLARSYSTEM_PLANET_H

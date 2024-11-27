#ifndef SATELLITE_H
#define SATELLITE_H

#include "CelestialBody.h"
#include "Planet.h"

class Satellite : public CelestialBody {
private:
    Planet* parentPlanet;
    float orbitRadius;
    float orbitAngle;
    float orbitSpeed;

public:
    Satellite(Planet* planet, float distance, float radius, sf::Color color, const std::string& name, float speed);
    void update(float deltaTime) override;
};

#endif // SATELLITE_H

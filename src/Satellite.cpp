#include "Satellite.h"
#include <cmath>

Satellite::Satellite(Planet* planet, float distance, float radius, sf::Color color, const std::string& name, float speed) 
    : CelestialBody(planet->getPosition().x + distance, planet->getPosition().y, radius, color, name),
      parentPlanet(planet), orbitRadius(distance), orbitAngle(0), 
      orbitSpeed(speed) {}

void Satellite::update(float deltaTime) {
    orbitAngle += orbitSpeed * deltaTime;
    position.x = parentPlanet->getPosition().x + std::cos(orbitAngle) * orbitRadius;
    position.y = parentPlanet->getPosition().y + std::sin(orbitAngle) * orbitRadius;
    shape.setPosition(position);
}

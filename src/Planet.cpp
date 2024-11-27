#include "Planet.h"
#include <cmath>

Planet::Planet(Star* star, float distance, float radius, sf::Color color, const std::string& name, float speed) 
    : CelestialBody(star->getPosition().x + distance, star->getPosition().y, radius, color, name),
      parentStar(star), orbitRadius(distance), orbitAngle(0), 
      orbitSpeed(speed) {}

void Planet::update(float deltaTime) {
    orbitAngle += orbitSpeed * deltaTime;
    position.x = parentStar->getPosition().x + std::cos(orbitAngle) * orbitRadius;
    position.y = parentStar->getPosition().y + std::sin(orbitAngle) * orbitRadius;
    shape.setPosition(position);
}

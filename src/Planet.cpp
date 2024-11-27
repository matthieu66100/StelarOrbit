#include "Planet.h"
#include <cmath>

// Vitesses de rotation approximatives en degrés par seconde
const float MERCURY_ROT = 10.83f;
const float VENUS_ROT = -2.64f;    // Rotation rétrograde
const float EARTH_ROT = 360.0f;    // Une rotation complète par jour
const float MARS_ROT = 350.89f;
const float JUPITER_ROT = 870.27f;
const float SATURN_ROT = 810.76f;
const float URANUS_ROT = -501.16f; // Rotation rétrograde
const float NEPTUNE_ROT = 536.31f;

Planet::Planet(Star* star, float distance, float radius, sf::Color color, const std::string& name, float speed) 
    : CelestialBody(star->getPosition().x + distance, star->getPosition().y, radius, 
                    "ressources/img/" + name + ".png", name, getRotationSpeed(name), color),
      parentStar(star), orbitRadius(distance), orbitAngle(0), orbitSpeed(speed) {}

float Planet::getRotationSpeed(const std::string& name) {
    if (name == "Mercury") return MERCURY_ROT;
    if (name == "Venus") return VENUS_ROT;
    if (name == "Earth") return EARTH_ROT;
    if (name == "Mars") return MARS_ROT;
    if (name == "Jupiter") return JUPITER_ROT;
    if (name == "Saturn") return SATURN_ROT;
    if (name == "Uranus") return URANUS_ROT;
    if (name == "Neptune") return NEPTUNE_ROT;
    return EARTH_ROT; // Default
}

void Planet::update(float deltaTime) {
    orbitAngle += orbitSpeed * deltaTime;
    position.x = parentStar->getPosition().x + std::cos(orbitAngle) * orbitRadius;
    position.y = parentStar->getPosition().y + std::sin(orbitAngle) * orbitRadius;
    if (useTexture) {
        sprite.setPosition(position);
    } else {
        shape.setPosition(position);
    }
    updateRotation(deltaTime);
}

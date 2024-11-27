#include "Satellite.h"
#include <cmath>

// Vitesses de rotation des satellites en degrés par seconde
const float MOON_ROT = 13.2f;      // La Lune fait une rotation par mois
const float DEFAULT_SAT_ROT = 20.0f; // Valeur par défaut pour les autres satellites

Satellite::Satellite(Planet* planet, float distance, float radius, sf::Color color, const std::string& name, float speed) 
    : CelestialBody(planet->getPosition().x + distance, planet->getPosition().y, radius,
                    "ressources/img/" + name + ".png", name, 
                    (name == "Moon" ? MOON_ROT : DEFAULT_SAT_ROT), color),
      parentPlanet(planet), orbitRadius(distance), orbitAngle(0), orbitSpeed(speed) {}

void Satellite::update(float deltaTime) {
    orbitAngle += orbitSpeed * deltaTime;
    position.x = parentPlanet->getPosition().x + std::cos(orbitAngle) * orbitRadius;
    position.y = parentPlanet->getPosition().y + std::sin(orbitAngle) * orbitRadius;
    if (useTexture) {
        sprite.setPosition(position);
    } else {
        shape.setPosition(position);
    }
    updateRotation(deltaTime);
}

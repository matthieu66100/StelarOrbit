#include "Star.h"

Star::Star(float x, float y, float radius) 
    : CelestialBody(x, y, radius, "ressources/img/Sun.png", "Sun", 2.0f, sf::Color::Yellow) {}

void Star::update(float deltaTime) {
    updateRotation(deltaTime);
}

#include "Star.h"

Star::Star(float x, float y, float radius) 
    : CelestialBody(x, y, radius, sf::Color::Yellow, "Soleil") {}

void Star::update(float deltaTime) {}

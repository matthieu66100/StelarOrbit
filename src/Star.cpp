#include "Star.h"

Star::Star(float x, float y, float radius) 
    : CelestialBody(x, y, radius, "ressources/img/Sun.png", "Sun", sf::Color::Yellow) {}

void Star::update(float deltaTime) {}

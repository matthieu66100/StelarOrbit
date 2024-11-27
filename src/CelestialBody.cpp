#include "CelestialBody.h"

CelestialBody::CelestialBody(float x, float y, float radius, sf::Color bodyColor, const std::string& bodyName)
    : position(x, y), mass(radius * 10), color(bodyColor), name(bodyName) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
}

void CelestialBody::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f CelestialBody::getPosition() const { 
    return position; 
}

std::string CelestialBody::getName() const { 
    return name; 
}

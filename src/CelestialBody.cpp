#include "CelestialBody.h"

CelestialBody::CelestialBody(float x, float y, float radius, const std::string& texturePath, 
                            const std::string& bodyName, sf::Color fallbackColor)
    : position(x, y), mass(radius * 10), name(bodyName), radius(radius), color(fallbackColor) {
    
    // Try to load texture
    useTexture = texture.loadFromFile(texturePath);
    
    if (useTexture) {
        sprite.setTexture(texture);
        float textureRadius = texture.getSize().x / 2.0f;
        float scale = (radius * 2) / texture.getSize().x;
        sprite.setScale(scale, scale);
        sprite.setOrigin(textureRadius, textureRadius);
        sprite.setPosition(position);
    } else {
        // Fallback to circle shape
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);
        shape.setPosition(position);
    }
}

void CelestialBody::draw(sf::RenderWindow& window) {
    if (useTexture) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::Vector2f CelestialBody::getPosition() const { 
    return position; 
}

std::string CelestialBody::getName() const { 
    return name; 
}

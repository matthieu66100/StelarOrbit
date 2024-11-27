#ifndef SOLARSYSTEM_CELESTIALBODY_H
#define SOLARSYSTEM_CELESTIALBODY_H

#include <SFML/Graphics.hpp>
#include <string>

class CelestialBody {
protected:
    sf::Vector2f position;
    float mass;
    sf::Color color;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::CircleShape shape;
    std::string name;
    float radius;
    bool useTexture;

public:
    CelestialBody(float x, float y, float radius, const std::string& texturePath, const std::string& bodyName, sf::Color fallbackColor = sf::Color::White);
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    std::string getName() const;
};

#endif // SOLARSYSTEM_CELESTIALBODY_H

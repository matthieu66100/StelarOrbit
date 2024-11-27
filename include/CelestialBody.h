#ifndef SOLARSYSTEM_CELESTIALBODY_H
#define SOLARSYSTEM_CELESTIALBODY_H

#include <SFML/Graphics.hpp>
#include <string>

class CelestialBody {
protected:
    sf::Vector2f position;
    float mass;
    sf::Color color;
    sf::CircleShape shape;
    std::string name;

public:
    CelestialBody(float x, float y, float radius, sf::Color bodyColor, const std::string& bodyName);
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    std::string getName() const;
};

#endif // SOLARSYSTEM_CELESTIALBODY_H

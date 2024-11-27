#ifndef SOLARSYSTEM_SOLARSYSTEM_H
#define SOLARSYSTEM_SOLARSYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Star.h"
#include "Planet.h"
#include "Satellite.h"

class SolarSystem {
private:
    sf::RenderWindow& window;
    Star* star;
    std::vector<Planet*> planets;
    std::vector<Satellite*> satellites;
    bool isPaused;
    float simulationSpeed;

public:
    SolarSystem(sf::RenderWindow& window);
    ~SolarSystem();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void togglePause();
    bool getPauseState() const { return isPaused; }
    void increaseSpeed();
    void decreaseSpeed();
};

#endif // SOLARSYSTEM_SOLARSYSTEM_H

#include "SolarSystem.h"
#include <iomanip>
#include <sstream>
#include <cmath>

// Define M_PI if not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SolarSystem::SolarSystem(sf::RenderWindow& win) : window(win), isPaused(false), simulationSpeed(1.0f) {
    // Create the Sun
    star = new Star(window.getSize().x / 2.f, window.getSize().y / 2.f, 50.f);
    
    // Create Mercury
    planets.push_back(new Planet(star, 100.f, 8.f, sf::Color(169, 169, 169), "Mercury", 1.607f));
    
    // Create Venus
    planets.push_back(new Planet(star, 150.f, 15.f, sf::Color(255, 198, 73), "Venus", 1.174f));
    
    // Create Earth and Moon
    Planet* earth = new Planet(star, 200.f, 16.f, sf::Color(100, 149, 237), "Earth", 1.0f);
    planets.push_back(earth);
    satellites.push_back(new Satellite(earth, 30.f, 4.f, sf::Color::White, "Moon", 2.0f));
    
    // Create Mars and its moons
    Planet* mars = new Planet(star, 250.f, 12.f, sf::Color(193, 68, 14), "Mars", 0.802f);
    planets.push_back(mars);
    satellites.push_back(new Satellite(mars, 20.f, 2.f, sf::Color(169, 169, 169), "Phobos", 2.5f));
    satellites.push_back(new Satellite(mars, 25.f, 1.f, sf::Color(169, 169, 169), "Deimos", 2.2f));
    
    // Create Jupiter and its main moons
    Planet* jupiter = new Planet(star, 350.f, 35.f, sf::Color(255, 198, 73), "Jupiter", 0.434f);
    planets.push_back(jupiter);
    satellites.push_back(new Satellite(jupiter, 45.f, 5.f, sf::Color(238, 232, 205), "Io", 2.8f));
    satellites.push_back(new Satellite(jupiter, 50.f, 4.f, sf::Color::White, "Europa", 2.5f));
    satellites.push_back(new Satellite(jupiter, 55.f, 6.f, sf::Color(169, 169, 169), "Ganymede", 2.2f));
    satellites.push_back(new Satellite(jupiter, 60.f, 5.f, sf::Color(238, 232, 205), "Callisto", 2.0f));
    
    // Create Saturn and its main moons
    Planet* saturn = new Planet(star, 450.f, 30.f, sf::Color(238, 232, 205), "Saturn", 0.323f);
    planets.push_back(saturn);
    satellites.push_back(new Satellite(saturn, 40.f, 3.f, sf::Color::White, "Titan", 2.4f));
    satellites.push_back(new Satellite(saturn, 45.f, 2.f, sf::Color(169, 169, 169), "Rhea", 2.2f));
    
    // Create Uranus and its main moons
    Planet* uranus = new Planet(star, 520.f, 20.f, sf::Color(173, 216, 230), "Uranus", 0.228f);
    planets.push_back(uranus);
    satellites.push_back(new Satellite(uranus, 30.f, 3.f, sf::Color::White, "Titania", 2.3f));
    satellites.push_back(new Satellite(uranus, 35.f, 3.f, sf::Color(169, 169, 169), "Oberon", 2.1f));
    
    // Create Neptune and its main moons
    Planet* neptune = new Planet(star, 580.f, 19.f, sf::Color(0, 0, 128), "Neptune", 0.182f);
    planets.push_back(neptune);
    satellites.push_back(new Satellite(neptune, 35.f, 4.f, sf::Color::White, "Triton", 2.3f));
}

SolarSystem::~SolarSystem() {
    delete star;
    for (auto planet : planets) delete planet;
    for (auto satellite : satellites) delete satellite;
}

void SolarSystem::update(float deltaTime) {
    if (isPaused) return;
    
    float adjustedDeltaTime = deltaTime * simulationSpeed;
    
    // Calculate elapsed days based on Earth's orbit
    Planet* earth = planets[2];
    float earthOrbitAngle = earth->getOrbitAngle();
    float days = (earthOrbitAngle / (2 * M_PI)) * 365.25;
    
    // Update text display
    textDisplay.update(days);
    
    // Update all celestial bodies
    star->update(adjustedDeltaTime);
    for (auto planet : planets) planet->update(adjustedDeltaTime);
    for (auto satellite : satellites) satellite->update(adjustedDeltaTime);
}

void SolarSystem::draw(sf::RenderWindow& window) {
    star->draw(window);
    for (auto planet : planets) planet->draw(window);
    for (auto satellite : satellites) satellite->draw(window);
    textDisplay.draw(window);
}

void SolarSystem::togglePause() {
    isPaused = !isPaused;
}

void SolarSystem::increaseSpeed() {
    simulationSpeed = std::min(simulationSpeed * 1.5f, 10.0f);
}

void SolarSystem::decreaseSpeed() {
    simulationSpeed = std::max(simulationSpeed * 0.75f, 0.1f);
}

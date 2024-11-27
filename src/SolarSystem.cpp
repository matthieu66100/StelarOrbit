#include "SolarSystem.h"
#include <iomanip>
#include <sstream>
#include <cmath>

// Pour définir M_PI si ce n'est pas déjà fait
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SolarSystem::SolarSystem(sf::RenderWindow& win) : window(win), isPaused(false), simulationSpeed(1.0f), elapsedDays(0) {
    // Chargement de la police
    if (!font.loadFromFile("resources/arial.ttf")) {
        // Si la police personnalisée n'est pas trouvée, on utilise la police système
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            // Si même la police système n'est pas trouvée, on lance une exception
            throw std::runtime_error("Impossible de charger la police");
        }
    }
    
    // Configuration du texte
    dateText.setFont(font);
    dateText.setCharacterSize(20);
    dateText.setFillColor(sf::Color::White);
    dateText.setPosition(10, 10);
    
    // Soleil
    star = new Star(window.getSize().x / 2.f, window.getSize().y / 2.f, 50.f);
    
    // Mercure
    planets.push_back(new Planet(star, 100.f, 8.f, sf::Color(169, 169, 169), "Mercure", 1.607f));
    
    // Vénus
    planets.push_back(new Planet(star, 150.f, 15.f, sf::Color(255, 198, 73), "Venus", 1.174f));
    
    // Terre et Lune
    Planet* earth = new Planet(star, 200.f, 16.f, sf::Color(100, 149, 237), "Terre", 1.0f);
    planets.push_back(earth);
    satellites.push_back(new Satellite(earth, 30.f, 4.f, sf::Color::White, "Lune", 2.0f));
    
    // Mars et ses lunes
    Planet* mars = new Planet(star, 250.f, 12.f, sf::Color(193, 68, 14), "Mars", 0.802f);
    planets.push_back(mars);
    satellites.push_back(new Satellite(mars, 20.f, 2.f, sf::Color(169, 169, 169), "Phobos", 2.5f));
    satellites.push_back(new Satellite(mars, 25.f, 1.f, sf::Color(169, 169, 169), "Deimos", 2.2f));
    
    // Jupiter et ses principales lunes
    Planet* jupiter = new Planet(star, 350.f, 35.f, sf::Color(255, 198, 73), "Jupiter", 0.434f);
    planets.push_back(jupiter);
    satellites.push_back(new Satellite(jupiter, 45.f, 5.f, sf::Color(238, 232, 205), "Io", 2.8f));
    satellites.push_back(new Satellite(jupiter, 50.f, 4.f, sf::Color::White, "Europe", 2.5f));
    satellites.push_back(new Satellite(jupiter, 55.f, 6.f, sf::Color(169, 169, 169), "Ganymede", 2.2f));
    satellites.push_back(new Satellite(jupiter, 60.f, 5.f, sf::Color(238, 232, 205), "Callisto", 2.0f));
    
    // Saturne et ses principales lunes
    Planet* saturn = new Planet(star, 450.f, 30.f, sf::Color(238, 232, 205), "Saturne", 0.323f);
    planets.push_back(saturn);
    satellites.push_back(new Satellite(saturn, 40.f, 3.f, sf::Color::White, "Titan", 2.4f));
    satellites.push_back(new Satellite(saturn, 45.f, 2.f, sf::Color(169, 169, 169), "Rhea", 2.2f));
    
    // Uranus et ses principales lunes
    Planet* uranus = new Planet(star, 520.f, 20.f, sf::Color(173, 216, 230), "Uranus", 0.228f);
    planets.push_back(uranus);
    satellites.push_back(new Satellite(uranus, 30.f, 3.f, sf::Color::White, "Titania", 2.3f));
    satellites.push_back(new Satellite(uranus, 35.f, 3.f, sf::Color(169, 169, 169), "Oberon", 2.1f));
    
    // Neptune et ses principales lunes
    Planet* neptune = new Planet(star, 580.f, 19.f, sf::Color(0, 0, 128), "Neptune", 0.182f);
    planets.push_back(neptune);
    satellites.push_back(new Satellite(neptune, 35.f, 4.f, sf::Color::White, "Triton", 2.3f));
}

SolarSystem::~SolarSystem() {
    delete star;
    for (auto planet : planets) delete planet;
    for (auto satellite : satellites) delete satellite;
}

std::string SolarSystem::getCurrentDate() const {
    // On part du 1er janvier 2024
    time_t baseTime = 1704067200; // timestamp pour 01/01/2024
    time_t currentTime = baseTime + static_cast<time_t>(elapsedDays * 86400); // 86400 secondes par jour
    
    struct tm* timeinfo = localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(timeinfo, "%d/%m/%Y");
    return ss.str();
}

void SolarSystem::update(float deltaTime) {
    if (isPaused) return;
    
    float adjustedDeltaTime = deltaTime * simulationSpeed;
    
    // Mise à jour des jours écoulés (1 tour complet = 365.25 jours)
    // On utilise la position angulaire de la Terre pour calculer la date
    Planet* earth = planets[2]; // La Terre est la 3ème planète
    float earthOrbitAngle = earth->getOrbitAngle();
    elapsedDays = (earthOrbitAngle / (2 * M_PI)) * 365.25;
    
    star->update(adjustedDeltaTime);
    for (auto planet : planets) planet->update(adjustedDeltaTime);
    for (auto satellite : satellites) satellite->update(adjustedDeltaTime);
}

void SolarSystem::draw(sf::RenderWindow& window) {
    star->draw(window);
    for (auto planet : planets) planet->draw(window);
    for (auto satellite : satellites) satellite->draw(window);
    
    // Mise à jour et affichage de la date
    dateText.setString(getCurrentDate());
    window.draw(dateText);
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

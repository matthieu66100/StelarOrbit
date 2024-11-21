#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <memory>

class CelestialBody {
protected:
    sf::Vector2f position;
    float mass;
    sf::Color color;
    sf::CircleShape shape;
    std::string name;

public:
    CelestialBody(float x, float y, float radius, sf::Color bodyColor, const std::string& bodyName) 
        : position(x, y), mass(radius * 10), color(bodyColor), name(bodyName) {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);
        shape.setPosition(position);
    }

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const { return position; }
    std::string getName() const { return name; }
};

class Star : public CelestialBody {
public:
    Star(float x, float y, float radius) 
        : CelestialBody(x, y, radius, sf::Color::Yellow, "Soleil") {}

    void update(float deltaTime) override {}
};

class Planet : public CelestialBody {
private:
    Star* parentStar;
    float orbitRadius;
    float orbitAngle;
    float orbitSpeed;

public:
    Planet(Star* star, float distance, float radius, sf::Color color, const std::string& name, float speed) 
        : CelestialBody(star->getPosition().x + distance, star->getPosition().y, radius, color, name),
          parentStar(star), orbitRadius(distance), orbitAngle(0), 
          orbitSpeed(speed) {}

    void update(float deltaTime) override {
        orbitAngle += orbitSpeed * deltaTime;
        position.x = parentStar->getPosition().x + std::cos(orbitAngle) * orbitRadius;
        position.y = parentStar->getPosition().y + std::sin(orbitAngle) * orbitRadius;
        shape.setPosition(position);
    }
};

class Satellite : public CelestialBody {
private:
    Planet* parentPlanet;
    float orbitRadius;
    float orbitAngle;
    float orbitSpeed;

public:
    Satellite(Planet* planet, float distance, float radius, sf::Color color, const std::string& name, float speed) 
        : CelestialBody(planet->getPosition().x + distance, planet->getPosition().y, radius, color, name),
          parentPlanet(planet), orbitRadius(distance), orbitAngle(0), 
          orbitSpeed(speed) {}

    void update(float deltaTime) override {
        orbitAngle += orbitSpeed * deltaTime;
        position.x = parentPlanet->getPosition().x + std::cos(orbitAngle) * orbitRadius;
        position.y = parentPlanet->getPosition().y + std::sin(orbitAngle) * orbitRadius;
        shape.setPosition(position);
    }
};

class SolarSystem {
private:
    Star centralStar;
    std::vector<std::unique_ptr<Planet>> planets;
    std::vector<std::unique_ptr<Satellite>> satellites;

public:
    SolarSystem(sf::RenderWindow& window) : 
        centralStar(window.getSize().x / 2.0f, window.getSize().y / 2.0f, 50) {
        float centerX = window.getSize().x / 2.0f;
        float centerY = window.getSize().y / 2.0f;

        // Mercure
        planets.push_back(std::make_unique<Planet>(&centralStar, 90, 5, sf::Color(128, 128, 128), "Mercure", 1.2f));
        
        // Vénus
        planets.push_back(std::make_unique<Planet>(&centralStar, 130, 7, sf::Color(255, 200, 100), "Vénus", 0.9f));
        
        // Terre et Lune
        auto* terre = new Planet(&centralStar, 180, 8, sf::Color(100, 150, 255), "Terre", 0.7f);
        planets.push_back(std::unique_ptr<Planet>(terre));
        satellites.push_back(std::make_unique<Satellite>(terre, 25, 3, sf::Color(200, 200, 200), "Lune", 2.0f));
        
        // Mars et ses lunes
        auto* mars = new Planet(&centralStar, 230, 6, sf::Color(255, 100, 0), "Mars", 0.6f);
        planets.push_back(std::unique_ptr<Planet>(mars));
        satellites.push_back(std::make_unique<Satellite>(mars, 20, 2, sf::Color(150, 150, 150), "Phobos", 3.0f));
        satellites.push_back(std::make_unique<Satellite>(mars, 30, 2, sf::Color(200, 200, 200), "Deimos", 2.5f));
        
        // Jupiter et ses principales lunes
        auto* jupiter = new Planet(&centralStar, 320, 20, sf::Color(200, 150, 100), "Jupiter", 0.4f);
        planets.push_back(std::unique_ptr<Planet>(jupiter));
        satellites.push_back(std::make_unique<Satellite>(jupiter, 40, 4, sf::Color(200, 180, 150), "Io", 2.0f));
        satellites.push_back(std::make_unique<Satellite>(jupiter, 60, 4, sf::Color(180, 160, 130), "Europe", 1.8f));
        satellites.push_back(std::make_unique<Satellite>(jupiter, 80, 5, sf::Color(160, 140, 110), "Ganymède", 1.5f));
        satellites.push_back(std::make_unique<Satellite>(jupiter, 100, 4, sf::Color(140, 120, 90), "Callisto", 1.3f));
        
        // Saturne et ses principales lunes
        auto* saturne = new Planet(&centralStar, 420, 17, sf::Color(210, 180, 140), "Saturne", 0.3f);
        planets.push_back(std::unique_ptr<Planet>(saturne));
        satellites.push_back(std::make_unique<Satellite>(saturne, 50, 3, sf::Color(200, 190, 170), "Titan", 1.7f));
        
        // Uranus
        planets.push_back(std::make_unique<Planet>(&centralStar, 540, 14, sf::Color(200, 230, 255), "Uranus", 0.2f));
        
        // Neptune
        planets.push_back(std::make_unique<Planet>(&centralStar, 650, 12, sf::Color(100, 100, 255), "Neptune", 0.1f));
    }

    void update(float deltaTime) {
        centralStar.update(deltaTime);
        for (auto& planet : planets) planet->update(deltaTime);
        for (auto& satellite : satellites) satellite->update(deltaTime);
    }

    void draw(sf::RenderWindow& window) {
        centralStar.draw(window);
        for (auto& planet : planets) planet->draw(window);
        for (auto& satellite : satellites) satellite->draw(window);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Simulation du Système Solaire", sf::Style::Fullscreen | sf::Style::Close);
    window.setFramerateLimit(60);

    SolarSystem solarSystem(window);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        solarSystem.update(deltaTime);

        window.clear(sf::Color::Black);
        solarSystem.draw(window);
        window.display();
    }

    return 0;
}

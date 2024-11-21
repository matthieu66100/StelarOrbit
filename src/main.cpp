#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace std;

// Classe de base pour les corps célestes
class CelestialBody {
protected:
    sf::CircleShape shape;
    float angle;

public:
    CelestialBody(float radius, const std::string& textureFile) : angle(0.0f) {
        shape.setRadius(radius);
        if (!textureFile.empty()) {
            sf::Texture texture;
            texture.loadFromFile(textureFile);
            shape.setTexture(&texture);
        }
    }

    virtual void updatePosition(float centerX, float centerY) = 0;

    sf::CircleShape getShape() const {
        return shape;
    }

    void setPosition(float x, float y) {
        shape.setPosition(x - shape.getRadius(), y - shape.getRadius());
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());
    }
};

// Classe pour représenter une étoile
class Star : public CelestialBody {
public:
    Star(float radius, const std::string& textureFile) : CelestialBody(radius, textureFile) {}

    void updatePosition(float centerX, float centerY) override {
        setPosition(centerX, centerY);
    }
};

// Classe pour représenter une planète
class Planet : public CelestialBody {
private:
    float distanceFromSun;
    float speed;
    float radius;

public:
    Planet(float radius, sf::Color color, float distanceFromSun, const std::string& textureFile = "")
        : CelestialBody(radius, textureFile), distanceFromSun(distanceFromSun) {
        shape.setFillColor(color);
    }

    float getDistanceFromSun() const { return distanceFromSun; }

    float getRadius() const {
        return radius;
    }

    void updatePosition(float centerX, float centerY) override {
        angle += speed;
        setPosition(centerX + distanceFromSun * cos(angle), centerY + distanceFromSun * sin(angle));
    }
};

// Classe pour représenter un satellite
class Satellite : public CelestialBody {
private:
    float distance;
    Planet* parentPlanet;
    float speed;

public:
    Satellite(float radius, sf::Color color, float speed, Planet* parent)
        : CelestialBody(radius * 0.05f, ""), parentPlanet(parent) {
        distance = parentPlanet->getRadius() * 2.0f;
        this->speed = speed;
        shape.setFillColor(color);
    }

    void updatePosition(float centerX, float centerY) override {
        angle += speed;
        sf::Vector2f planetPosition = parentPlanet->getPosition();
        setPosition(planetPosition.x + distance * cos(angle), planetPosition.y + distance * sin(angle));
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Spheres", sf::Style::Default);
    window.setFramerateLimit(60);

    // Création du soleil
    Star soleil(30, "ressources/soleil.png");
    soleil.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    // Création des planètes
    vector<Planet> planets = {
        Planet(3, sf::Color(128, 128, 128), 57.91),   // Mercure
        Planet(6, sf::Color::Yellow, 108.21), // Vénus
        Planet(6, sf::Color::Blue, 149.60),   // Terre
        Planet(4, sf::Color::Red, 227.92),    // Mars
        Planet(10, sf::Color(255, 165, 0), 778.57), // Jupiter
        Planet(9, sf::Color(218, 165, 32), 1433.5), // Saturne
        Planet(8, sf::Color::Cyan, 2872.5),    // Uranus
        Planet(7, sf::Color(0, 0, 139), 4495.1) // Neptune
    };

    // Création des satellites
    vector<Satellite> satellites = {
        Satellite(5, sf::Color::White, 0.02f, &planets[2]), // Lune de la Terre
        Satellite(3, sf::Color(255, 228, 196), 0.03f, &planets[3]), // Phobos de Mars
        Satellite(3, sf::Color(255, 228, 196), 0.01f, &planets[3]), // Deimos de Mars
        Satellite(6, sf::Color(255, 215, 0), 0.04f, &planets[4]), // Io de Jupiter
        Satellite(6, sf::Color(255, 215, 0), 0.05f, &planets[4]), // Europe de Jupiter
        Satellite(6, sf::Color(255, 215, 0), 0.06f, &planets[4]), // Ganymède de Jupiter
        Satellite(6, sf::Color(255, 215, 0), 0.07f, &planets[4]), // Callisto de Jupiter
        Satellite(6, sf::Color(255, 215, 0), 0.08f, &planets[5]), // Titan de Saturne
        Satellite(5, sf::Color(135, 206, 250), 0.09f, &planets[6]), // Titania d'Uranus
        Satellite(5, sf::Color(135, 206, 250), 0.1f, &planets[6]), // Oberon d'Uranus
        Satellite(5, sf::Color(0, 0, 139), 0.11f, &planets[7]) // Triton de Neptune
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(soleil.getShape()); // Dessiner le soleil

        // Mettre à jour et dessiner les planètes et leurs satellites
        for (auto& planet : planets) {
            planet.updatePosition(window.getSize().x / 2, window.getSize().y / 2);
            window.draw(planet.getShape());

            for (auto& satellite : satellites) {
                satellite.updatePosition(planet.getShape().getPosition().x, planet.getShape().getPosition().y);
                window.draw(satellite.getShape());
            }
        }

        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include "SolarSystem.h"

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Simulation du Système Solaire", sf::Style::Fullscreen | sf::Style::Close);
    window.setFramerateLimit(60);

    SolarSystem solarSystem(window);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    solarSystem.togglePause();
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        solarSystem.update(deltaTime);

        window.clear(sf::Color::Black);
        solarSystem.draw(window);
        window.display();
    }

    return 0;
}

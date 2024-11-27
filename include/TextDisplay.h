#ifndef SOLARSYSTEM_TEXTDISPLAY_H
#define SOLARSYSTEM_TEXTDISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

class TextDisplay {
private:
    sf::Font font;
    sf::Text dateText;
    float elapsedDays;
    std::string getCurrentDate() const;

public:
    TextDisplay();
    void update(float elapsedDays);
    void draw(sf::RenderWindow& window);
};

#endif // SOLARSYSTEM_TEXTDISPLAY_H 
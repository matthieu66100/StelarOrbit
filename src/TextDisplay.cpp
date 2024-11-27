#include "TextDisplay.h"
#include <iomanip>
#include <sstream>

TextDisplay::TextDisplay() : elapsedDays(0) {
    if (!font.loadFromFile("resources/arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            throw std::runtime_error("Impossible de charger la police");
        }
    }
    
    dateText.setFont(font);
    dateText.setCharacterSize(20);
    dateText.setFillColor(sf::Color::White);
    dateText.setPosition(10, 10);
}

std::string TextDisplay::getCurrentDate() const {
    time_t baseTime = 1704067200; // 01/01/2024
    time_t currentTime = baseTime + static_cast<time_t>(elapsedDays * 86400);
    
    struct tm* timeinfo = localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(timeinfo, "%d/%m/%Y");
    return ss.str();
}

void TextDisplay::update(float days) {
    elapsedDays = days;
    dateText.setString(getCurrentDate());
}

void TextDisplay::draw(sf::RenderWindow& window) {
    window.draw(dateText);
} 
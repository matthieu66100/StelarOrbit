#include "TextDisplay.h"
#include <iomanip>
#include <sstream>

TextDisplay::TextDisplay() : elapsedDays(0) {
    if (!font.loadFromFile("ressources/ARIAL.TTF")) {
        throw std::runtime_error("Cannot load font: ressources/ARIAL.TTF");
    }
    
    // Configure date text
    dateText.setFont(font);
    dateText.setCharacterSize(20);
    dateText.setFillColor(sf::Color::White);
    dateText.setPosition(10, 10);

    // Configure chronometer text
    chronoText.setFont(font);
    chronoText.setCharacterSize(20);
    chronoText.setFillColor(sf::Color::White);
    chronoText.setPosition(10, 35);
}

std::string TextDisplay::getCurrentDate() const {
    time_t baseTime = 1704067200; // 01/01/2024
    time_t currentTime = baseTime + static_cast<time_t>(elapsedDays * 86400);
    
    struct tm* timeinfo = localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(timeinfo, "%d/%m/%Y");
    return ss.str();
}

std::string TextDisplay::getChronoText() const {
    int totalSeconds = static_cast<int>(elapsedDays * 86400);
    
    int hours = (totalSeconds / 3600) % 24;
    int days = static_cast<int>(elapsedDays) % 30;
    int months = (static_cast<int>(elapsedDays) / 30) % 12;
    int years = static_cast<int>(elapsedDays) / 365;

    std::stringstream ss;
    ss << "Elapsed time: ";
    
    // If all values are 0, display just 0h
    if (years == 0 && months == 0 && days == 0 && hours == 0) {
        ss << "0h";
        return ss.str();
    }

    if (hours >= 0) ss << std::setfill('0') << std::setw(2) << hours << "h ";
    if (days >= 0) ss << std::setfill('0') << std::setw(2) << days << "d ";
    if (months >= 0) ss << std::setfill('0') << std::setw(2) << months << "m ";
    if (years > 0) ss << std::setfill('0') << std::setw(4) << years << "y";

    return ss.str();
}

void TextDisplay::update(float days) {
    elapsedDays = days;
    dateText.setString(getCurrentDate());
    chronoText.setString(getChronoText());
}

void TextDisplay::draw(sf::RenderWindow& window) {
    window.draw(dateText);
    window.draw(chronoText);
} 
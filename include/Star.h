#include <SFML/Graphics.hpp>
#include "CelestialBody.h"

class Star : public CelestialBosdy {
  
public:
  Star(float x, float y, float radius)
  : CelestialBosdy(x, y, radius, sf::Color::Yellow, "Soleil")

    void update(float deltaTime) override {}
};



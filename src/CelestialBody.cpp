
class CelestialBosdy {
protected:
  sf::Vector2f position;
  float mass;
  sf::Color color;
  sf::CircleShape shape;
  std::string name;


public:
  CelestialBody(float x, float y, float radius, sf::Color bodyColor, const std::string& bodyName)
  : postition(x,y), mass(radius * 10), color(bodyColor), name(bodyName){
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
  }

  virtual void update(float deltaTime) = 0;
  virtual void draw(sf::RenderWindow& window){
    window.draw(shape);
  }
  
  sf::Vector2f getPosition() const {
    return position;
  }
  std::string getName() const { 
    return name; 
  }

};

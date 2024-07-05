#pragma once
#include <SFML/Graphics.hpp>

class colision{
public:
    virtual sf::FloatRect getBounds() const = 0;
    bool isCollision(colision& col) const;

};

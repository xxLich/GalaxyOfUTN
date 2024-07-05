#ifndef FONDO_H_INCLUDED
#define FONDO_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Fondo{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
public:
    Fondo(const std::string& texturaPath);
    void draw(sf::RenderWindow& window) ;

};


#endif // FONDO_H_INCLUDED

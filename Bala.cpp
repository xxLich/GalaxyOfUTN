#include "Bala.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Colision.h"
Bala::Bala(float x, float y)
: _texture2(nullptr)
{
    _texture2 = new sf::Texture();
    if (!_texture2->loadFromFile("img/bala2.png")) {
       std::cout << "Error: No se pudo cargar la textura" << std::endl;

    }
    _sprite2.setTexture(*_texture2);
    _sprite2.setPosition(x, y);
    _velocidadBala = 15;
}

Bala::Bala(){}

void Bala::update() {
     _sprite2.move(0, -_velocidadBala);
}


void Bala::draw(sf::RenderWindow& window) {
    window.draw(_sprite2);
}


sf::Vector2f Bala::getPosition() const {
    return _sprite2.getPosition();
}

sf::FloatRect Bala::getBounds() const
{
    return _sprite2.getGlobalBounds();
}


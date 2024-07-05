
#include <iostream>
#include "bomba.h"
/////////BOMBA////////////

Bomba::Bomba(float x, float y): _texture3(nullptr) {
    _texture3 = new sf::Texture();
    if (!_texture3->loadFromFile("img/bomba.png")) {
        std::cout << "Error: No se pudo cargar la textura de la bomba" << std::endl;
    }
    _sprite3.setTexture(*_texture3);
    _sprite3.setPosition(x, y);
    _velocidadBomba = 6;
}

void Bomba::update() {
    _sprite3.move(0, _velocidadBomba);
}

void Bomba::draw(sf::RenderWindow& window) {
    window.draw(_sprite3);
}

sf::Vector2f Bomba::getPosition() const {
    return _sprite3.getPosition();
}
Bomba::~Bomba() {
    delete _texture3;
}
sf::FloatRect Bomba::getBounds() const {
    return _sprite3.getGlobalBounds(); // Ejemplo de implementación
}



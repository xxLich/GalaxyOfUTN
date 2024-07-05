#include "Personaje.h"
#include <iostream>
Personaje::Personaje(int v, const std::string& texturaPath) : _vida(v) {
    if (!_texture.loadFromFile(texturaPath)) {
        std::cout << "Error al cargar la textura desde " << texturaPath << std::endl;
    }
    _sprite.setTexture(_texture);
}

   void Personaje::draw(sf::RenderWindow& window) {
    window.draw(_sprite);
}

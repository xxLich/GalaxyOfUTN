#include "Fondo.h"

Fondo::Fondo(const std::string& texturaPath){

    if(!_texture.loadFromFile(texturaPath)){

    }
    _sprite.setTexture(_texture);
}

void Fondo::draw(sf::RenderWindow& window) {

    window.draw(_sprite);
}

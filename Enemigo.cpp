#include <iostream>
#include <cstdlib>
#include "Enemigo.h"
#include <algorithm>



Enemigo::Enemigo(int v, sf::Texture& textura, sf::Vector2f posicionInicial)
    : Personaje(v, "img/maxiano.png"), tiempoEntreBombas(2.0f)
{
    _sprite.setTexture(textura);
    //_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setPosition(posicionInicial);
    _velocidad = {4,4};
}

void Enemigo::update()
{
    _sprite.move(_velocidad);

if (_sprite.getPosition().x < 0) {
    _velocidad.x = std::abs(_velocidad.x);  // Cambiar a positiva si toca el borde izquierdo
}

if (_sprite.getPosition().y < 0) {
    _velocidad.y = std::abs(_velocidad.y);  // Cambiar a positiva si toca el borde superior
}

// Choca contra la pared
if (_sprite.getPosition().x + _sprite.getGlobalBounds().width > 1060) {
    _velocidad.x = -std::abs(_velocidad.x);  // Cambiar a negativa si toca el borde derecho
}

if (_sprite.getPosition().y + _sprite.getGlobalBounds().height > 600) {
    _velocidad.y = -std::abs(_velocidad.y);  // Cambiar a negativa si toca el borde inferior
}

    if (bombaClock.getElapsedTime().asSeconds() > 3) // Dispara cada tantos segundos
    {
        bombas.push_back(new Bomba(_sprite.getPosition().x, _sprite.getPosition().y));
        bombaClock.restart();
    }

    // Actualizar las bombas
    for (auto& bomba : bombas)
    {
        bomba->update();


    }

    // Eliminar bombas fuera de los límites de la pantalla
    bombas.erase(std::remove_if(bombas.begin(), bombas.end(), [](Bomba* b)
    {
        bool fueraDePantalla = b->getPosition().y > 898; // Ajusta el límite de la pantalla según sea necesario
        if (fueraDePantalla)
        {
            delete b;
        }
        return fueraDePantalla;
    }), bombas.end());
}

void Enemigo::lanzarBomba()
{
    bombas.push_back(new Bomba(_sprite.getPosition().x, _sprite.getPosition().y));
}

void Enemigo::draw(sf::RenderWindow& window)
{
    window.draw(_sprite);
    for (auto& bomba : bombas)
    {
        bomba->draw(window);
    }
}

sf::FloatRect Enemigo::getBounds() const
{
    return _sprite.getGlobalBounds();
}

std::vector<Bomba*>& Enemigo::getVectorBombas()
{
    return bombas;
}
void Enemigo::setScale(float x,float y){
        _sprite.setScale(x,y);
}
  void Enemigo::setVelocidad(float x, float y) {
        _velocidad.x = x;
        _velocidad.y = y;
    }

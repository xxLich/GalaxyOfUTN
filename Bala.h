#pragma once
#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED
#include "Colision.h"
#include <SFML/Graphics.hpp>

class Bala : public colision
{
     private:
           sf::Sprite _sprite2;
           sf::Texture *_texture2;
           int _velocidadBala;

     public:

        Bala(float x, float y);
        Bala();
        void update();
        void draw(sf::RenderWindow&);
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const override;

};



#endif // BALA_H_INCLUDED

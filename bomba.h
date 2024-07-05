#ifndef BOMBA_H_INCLUDED
#define BOMBA_H_INCLUDED
#include "Colision.h"
#include <SFML/Graphics.hpp>
class Bomba : public colision
{
private:
    sf::Sprite _sprite3;
    sf::Texture *_texture3;
    int _velocidadBomba;

public:

    Bomba(float x, float y);
    void update();
     ~Bomba();
    void draw(sf::RenderWindow&);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const override;

};

#endif // BOMBA_H_INCLUDED

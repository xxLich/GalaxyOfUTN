#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
class Personaje {
public:
    Personaje(int,const std::string&);
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window);

protected:
    int _vida;
    sf::Vector2f _velocidad;
    sf::Texture _texture;
    sf::Sprite _sprite;
};

#endif // PERSONAJE_H_INCLUDED

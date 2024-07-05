#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
const int Max_Menu = 4;
class Menu
{
private:
    int mainMenuSeleccionar;
    sf::Font font, fontVida;
    sf::Text menuItems[Max_Menu], textVida;
    sf::Sprite _bgdSprite;
    sf::Texture _bgdText;
    sf::Music music;
public:
    Menu(float ancho, float largo);
    void dibujar(sf::RenderWindow& window);
    void moverArriba();
    void moverAbajo();
    int mainMenuPresionar();

};


#endif // MENU_H_INCLUDED


#include "menu.h"

Menu::Menu(float ancho, float largo)
{
    if (!font.loadFromFile("font\\RETROTECH.ttf"))
    {
        std::cout << "No se pudo cargar la fuente" << std::endl;
    }

    // Carga de la textura del fondo
    if (!_bgdText.loadFromFile("img\\menuSinLetras.png"))
    {
        std::cout << "No se pudo cargar la imagen de fondo" << std::endl;
    }


    _bgdSprite.setTexture(_bgdText);
    _bgdSprite.setPosition(0, 0); // Posición inicial del sprite de fondo

    menuItems[0].setFont(font);
    menuItems[0].setFillColor(sf::Color::White);
    menuItems[0].setString("Jugar");
    menuItems[0].setCharacterSize(40);
    menuItems[0].setPosition(400, 600);





    menuItems[1].setFont(font);
    menuItems[1].setFillColor(sf::Color::White);
    menuItems[1].setString("Rankig");
    menuItems[1].setCharacterSize(40);
    menuItems[1].setPosition(400, 650);


    menuItems[2].setFont(font);
    menuItems[2].setFillColor(sf::Color::White);
    menuItems[2].setString("Equipo");
    menuItems[2].setCharacterSize(40);
    menuItems[2].setPosition(400, 700);

    // Salir
    menuItems[3].setFont(font);
    menuItems[3].setFillColor(sf::Color::White);
    menuItems[3].setString("Salir");
    menuItems[3].setCharacterSize(40);
    menuItems[3].setPosition(400, 750);

    mainMenuSeleccionar = 0;
    if (!music.openFromFile("song/sonidoSeleccion.ogg")) {
        std::cout << "No se pudo cargar el sonido de selección" << std::endl;
    }


}

void Menu::dibujar(sf::RenderWindow& window)
{
    window.draw(_bgdSprite);

    for (int i = 0; i < Max_Menu; i++)
    {
        window.draw(menuItems[i]);
    }


}


void Menu::moverArriba()
{
    music.play();
    menuItems[mainMenuSeleccionar].setFillColor(sf::Color::White);
    mainMenuSeleccionar--;

    if (mainMenuSeleccionar < 0)
    {
        mainMenuSeleccionar = Max_Menu - 1;
    }

    menuItems[mainMenuSeleccionar].setFillColor(sf::Color(0, 179, 186));
}

void Menu::moverAbajo()
{

    music.play();
    menuItems[mainMenuSeleccionar].setFillColor(sf::Color::White);
    mainMenuSeleccionar++;

    if (mainMenuSeleccionar == Max_Menu)
    {
        mainMenuSeleccionar = 0;
    }

    menuItems[mainMenuSeleccionar].setFillColor(sf::Color(0, 179, 186));
}

int Menu::mainMenuPresionar()
{
    return mainMenuSeleccionar;
}

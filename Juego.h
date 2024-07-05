#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>
#include "Fondo.h"
#include "Aliado.h"
#include "Enemigo.h"
#include "ContadorDeVida.h"
#include "contadorDeEliminaciones.h"
#include "contadorDeTiempo.h"

void inicializarJuego(sf::RenderWindow& window, Fondo*& fondo, Aliado*& simonecio,
                      sf::Texture& maxianoTexture, sf::Texture& brianTexture, sf::Texture& klosterianoTexture,
                      std::vector<Enemigo*>& maxianos, std::vector<Enemigo*>& brians,
                      std::vector<Enemigo*>& klosterianos, ContadorDeVida*& vida,
                      ContadorDeVida*& vidaKloster, contadorDeEliminaciones*& contador,
                      Cronometro*& tiempo, bool& eliminacion, int& contBrian, int& contMaxi);
                      void inicializarJuego(sf::RenderWindow& window, Fondo*& fondo, Aliado*& simonecio,
                      sf::Texture& maxianoTexture, sf::Texture& brianTexture, sf::Texture& klosterianoTexture,
                      std::vector<Enemigo*>& maxianos, std::vector<Enemigo*>& brians,
                      std::vector<Enemigo*>& klosterianos, ContadorDeVida*& vida,
                      ContadorDeVida*& vidaKloster, contadorDeEliminaciones*& contador,
                      Cronometro*& tiempo, bool& eliminacion, int& contBrian, int& contMaxi)
{
    fondo = new Fondo("img/fondo.png");
    simonecio = new Aliado(3, "img/simonecio.png");

    maxianoTexture.loadFromFile("img/maxiano.png");
    brianTexture.loadFromFile("img/brian.png");
    klosterianoTexture.loadFromFile("img/klosteriano.png");

    maxianos.clear();
    brians.clear();
    klosterianos.clear();

    for (int i = 0; i < 5; ++i)
    {
        sf::Vector2f randomPosition = sf::Vector2f(
            std::rand() % (window.getSize().x - maxianoTexture.getSize().x),
            std::rand() % (window.getSize().y - maxianoTexture.getSize().y)
        );
        maxianos.emplace_back(new Enemigo(1, maxianoTexture, randomPosition));
    }
    for (int i = 0; i < 5; ++i)
    {
        sf::Vector2f randomPosition = sf::Vector2f(
            std::rand() % (window.getSize().x - brianTexture.getSize().x),
            std::rand() % (window.getSize().y - brianTexture.getSize().y)
        );
        brians.emplace_back(new Enemigo(1, brianTexture, randomPosition));
    }

    vida = new ContadorDeVida(3);
    vidaKloster = new ContadorDeVida(10);
    contador = new contadorDeEliminaciones();
    tiempo = new Cronometro();
    tiempo->iniciar();

    eliminacion = true;
    contBrian = 0;
    contMaxi = 0;
}

void limpiarJuego(Fondo*& fondo, Aliado*& simonecio,
                  std::vector<Enemigo*>& maxianos, std::vector<Enemigo*>& brians,
                  std::vector<Enemigo*>& klosterianos, ContadorDeVida*& vida,
                  ContadorDeVida*& vidaKloster, contadorDeEliminaciones*& contador,
                  Cronometro*& tiempo)
{
    delete fondo;
    delete simonecio;
    delete vida;
    delete vidaKloster;
    delete contador;
    delete tiempo;

    for (Enemigo* enemigo : maxianos) delete enemigo;
    for (Enemigo* enemigo : brians) delete enemigo;
    for (Enemigo* enemigo : klosterianos) delete enemigo;

    maxianos.clear();
    brians.clear();
    klosterianos.clear();

    fondo = nullptr;
    simonecio = nullptr;
    vida = nullptr;
    vidaKloster = nullptr;
    contador = nullptr;
    tiempo = nullptr;
}

#endif // JUEGO_H_INCLUDED

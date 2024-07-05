#ifndef CONTADOR_DE_VIDA_H
#define CONTADOR_DE_VIDA_H

#include <SFML/Graphics.hpp>
#include <string>

class ContadorDeVida {

private:
    int vida;
    sf::Font font;
    sf::Text text;



public:
    ContadorDeVida(int vidaInicial);

    void dibujar(sf::RenderWindow& window);

    void disminuirVida(int cantidad);

    void aumentarVida(int cantidad);

    int obtenerVida() const;

    void posicionVida(int x, int y,sf::RenderWindow& window);
    void reiniciar(int vidaInicial);
};

#endif // CONTADOR_DE_VIDA_H


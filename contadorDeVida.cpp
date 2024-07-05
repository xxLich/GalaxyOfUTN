#include "contadorDeVida.h"


ContadorDeVida::ContadorDeVida(int vidaInicial) : vida(vidaInicial) {
    font.loadFromFile("font\\RETROTECH.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

}

void ContadorDeVida::reiniciar(int vidaInicial) {
        vida = vidaInicial;
    }
void ContadorDeVida::dibujar(sf::RenderWindow& window) {
    text.setString("Vidas: " + std::to_string(vida));
    text.setPosition(990, 10);


    window.draw(text);

}

void ContadorDeVida::disminuirVida(int cantidad) {
    vida -= cantidad;
    if (vida < 0) {
        vida = 0;
    }

}

void ContadorDeVida::aumentarVida(int cantidad) {
    vida += cantidad;

}

int ContadorDeVida::obtenerVida() const {
    return vida;
}
void ContadorDeVida::posicionVida(int x, int y,sf::RenderWindow& window){

    text.setString("Vida Klosteriano: " + std::to_string(vida));
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Red);
    window.draw(text);


}


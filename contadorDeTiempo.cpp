#include "contadorDeTiempo.h"
#include <iostream>

Cronometro::Cronometro() {
    tiempoInicio = sf::Time::Zero;
    tiempoTranscurrido = sf::Time::Zero;

}

void Cronometro::iniciar() {
    tiempoInicio = clock.getElapsedTime() - tiempoTranscurrido;
}

void Cronometro::detener() {
    tiempoTranscurrido = clock.getElapsedTime() - tiempoInicio;
}

void Cronometro::reiniciar() {
    tiempoInicio = clock.getElapsedTime();
    tiempoTranscurrido = sf::Time::Zero;
}

void Cronometro::actualizar() {

    tiempoTranscurrido = clock.getElapsedTime();

}


void Cronometro::dibujar(sf::RenderWindow& window) {
    fontTiempo.loadFromFile("font\\RETROTECH.ttf");
    textTiempo.setFont(fontTiempo);
    textTiempo.setCharacterSize(24);
    textTiempo.setFillColor(sf::Color::White);
    textTiempo.setString("Tiempo: " + std::to_string(static_cast<int>(tiempoTranscurrido.asSeconds())));
    textTiempo.setPosition(950, 30);
    window.draw(textTiempo);
}

float Cronometro::obtenerTiempoTranscurrido() const {
    return tiempoTranscurrido.asSeconds();
}

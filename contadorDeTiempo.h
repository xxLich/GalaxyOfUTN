#ifndef CONTADOR_DE_TIEMPO_H
#define CONTADOR_DE_TIEMPO_H

#include <SFML/Graphics.hpp>

class Cronometro {
private:
    sf::Clock clock;
    sf::Time tiempoInicio;
    sf::Time tiempoTranscurrido;
    sf::Text textTiempo;
    sf::Font fontTiempo;
public:
    Cronometro();

    void iniciar();
    void detener();
    void reiniciar();
    void actualizar();
    void dibujar(sf::RenderWindow& ventana);
    float obtenerTiempoTranscurrido() const;

};

#endif


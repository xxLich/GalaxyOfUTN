#ifndef CONTADORDEELIMINACIONES_H_INCLUDED
#define CONTADORDEELIMINACIONES_H_INCLUDED

class contadorDeEliminaciones {
private:
    int eliminacionesMaxianos;
    int eliminacionesBrians;
    sf::Font fuente;
    sf::Text textMaxiano;
    sf::Text textBrians;
    sf::Texture eliminacionTexture;
    sf::Sprite spriteEliminacion;

public:
    contadorDeEliminaciones() : eliminacionesMaxianos(0), eliminacionesBrians(0) {
        fuente.loadFromFile("font/RETROTECH.ttf");
        textMaxiano.setFont(fuente);
        textMaxiano.setFont(fuente);
        textMaxiano.setCharacterSize(24);
        textMaxiano.setFillColor(sf::Color::White);
        textMaxiano.setPosition(200, 150);

        textBrians.setFont(fuente);
        textBrians.setCharacterSize(24);
        textBrians.setFillColor(sf::Color::White);
        textBrians.setPosition(200, 215);

        eliminacionTexture.loadFromFile("img/marcoeliminaciones.png");
        spriteEliminacion.setTexture(eliminacionTexture);
        spriteEliminacion.setPosition(10, 100);
    }

    void contadorBrians() {
        eliminacionesBrians++;
    }

    void contadorMaxianos() {
        eliminacionesMaxianos++;
    }

    void actualizarTexto() {

        textBrians.setString(std::to_string(eliminacionesBrians) + " - 15");
        textMaxiano.setString(std::to_string(eliminacionesMaxianos) + " - 15");
    }

    void draw(sf::RenderWindow& window) {
        window.draw(spriteEliminacion);
        window.draw(textMaxiano);
        window.draw(textBrians);
    }
};

#endif // CONTADORDEELIMINACIONES_H_INCLUDED

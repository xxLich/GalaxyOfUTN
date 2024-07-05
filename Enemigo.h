#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED
#include "Personaje.h"
#include "Bala.h"
#include "bomba.h"
#include "colision.h"
#include <vector>
#include "Aliado.h"
class Enemigo : public Personaje, public colision {
private:
    int _timeRespawn;
    sf::Vector2f _newPosition;
    sf::Clock bombaClock;
    float tiempoEntreBombas;
public:

    Enemigo(int v, sf::Texture& textura, sf::Vector2f posicionInicial);
    std::vector<Bomba*> bombas;
    std::vector<Bomba*>&getVectorBombas();
    void update();
    void lanzarBomba();
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    void setScale(float x, float y);
    void setVelocidad(float x,float y);

};

#endif // ENEMIGO_H_INCLUDED

#ifndef ALIADO_H_INCLUDED
#define ALIADO_H_INCLUDED
#include "Personaje.h"
#include "Bala.h"
#include "Colision.h"
#include <vector>
#include <SFML/Audio.hpp>
class Aliado : public Personaje , public colision{
private:
     sf::Music _disparoSonido;
     sf::Vector2f gunMuzzle;

public:
    Aliado(int v, const std::string& texturaPath);
    void update() override;
    bool disparo();
    sf::Vector2f pos();
    void draw(sf::RenderWindow& window) override;
    std::vector<Bala*> balas;
    sf::Vector2f getMuzzlePosition() const;
    sf::Clock clock;
    std::vector<Bala*>&getVectorBalas();
    sf::FloatRect getBounds() const  {
    return _sprite.getGlobalBounds();
    }
};




#endif // ALIADO_H_INCLUDED

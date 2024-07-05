#include "Aliado.h"
#include "bomba.h"
Aliado::Aliado(int v, const std::string& texturaPath)
    : Personaje(v, texturaPath) {

     _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height/2 );
     _sprite.setPosition(0,898);
    _disparoSonido.openFromFile("song/disparoSimonecio.ogg");

    }

    void Aliado::update() {

    _velocidad.x = 0;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _velocidad.x = -7;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _velocidad.x = 7;
    }


    _sprite.move(_velocidad);


    if (_velocidad.x < 0) {
        _sprite.setScale(-1, 1);
    } else if (_velocidad.x > 0) {
        _sprite.setScale(1, 1);
    }


    if (_sprite.getGlobalBounds().left < 0) {
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
    }

    if (_sprite.getGlobalBounds().top < 0) {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
    }

    if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 1080) {
        _sprite.setPosition(1080 - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }

    if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 898) {
        _sprite.setPosition(_sprite.getPosition().x, 898 - (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));

    }

    for ( Bala* bala : balas) {
        bala -> update();
        //bala->isCollision()
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (clock.getElapsedTime().asSeconds() > 0.5) { // Intervalo entre disparos
            sf::Vector2f muzzlePosition = getMuzzlePosition();
            balas.push_back(new Bala(muzzlePosition.x, muzzlePosition.y));
            _disparoSonido.play();
            clock.restart();
        }
    }


    balas.erase(std::remove_if(balas.begin(), balas.end(), [](const Bala* b) {
        return b->getPosition().y < 0;
    }), balas.end());

}

sf::Vector2f Aliado::getMuzzlePosition() const {
    sf::Vector2f muzzlePosition;
    float offsetXRight = -14; // Ajuste para la posición X cuando el personaje mira a la derecha
    float offsetXLeft = -5; // Ajuste para la posición X cuando el personaje mira a la izquierda
    float offsetY = 20; // Ajuste fino para la posición Y

    if (_sprite.getScale().x > 0) {
        // Si el personaje mira a la derecha
        muzzlePosition.x = _sprite.getPosition().x + _sprite.getGlobalBounds().width / 2 + offsetXRight;
    } else {
        // Si el personaje mira a la izquierda
        muzzlePosition.x = _sprite.getPosition().x - _sprite.getGlobalBounds().width / 2 + offsetXLeft;
    }
    muzzlePosition.y = _sprite.getPosition().y - _sprite.getGlobalBounds().height / 2 + offsetY;

    return muzzlePosition;
}

bool Aliado::disparo(){
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
       return true;


    }  {

      return false;
    }

 }

sf::Vector2f Aliado::pos(){

return _sprite.getOrigin();
}


 void Aliado::draw(sf::RenderWindow& window) {
    window.draw(_sprite);
    for (Bala* bala : balas) {
        bala->draw(window);
    }
 }

 std::vector <Bala*>&Aliado::getVectorBalas(){

        return balas;

 }

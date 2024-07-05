#include "Aliado.h"
#include "Enemigo.h"
#include "Fondo.h"
#include "vector"
#include "Bala.h"
#include "menu.h"
#include "Colision.h"
#include "contadorDeEliminaciones.h"
#include "contadorDeVida.h"
#include "contadorDeTiempo.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "bomba.h"
#include "archPuntos.h"
#include "Juego.h"
#include <sstream>  // Para std::ostringstream
#include <iomanip>
using namespace sf;


int main()
{


    sf::RenderWindow window(sf::VideoMode(1080, 898), "The Galaxy UTN");
    Menu menu(window.getSize().x, window.getSize().y);
    window.setFramerateLimit(60);

    Music music;
    music.openFromFile("song/fondoMenu.ogg");
    music.setVolume(30);
    Music sonidoColisionBomba;
    sonidoColisionBomba.openFromFile("song/sonidoMuerte.ogg");
    Music klosterBns;
    klosterBns.openFromFile("song/buenasGentes.wav");
    Music sonidoGameOver;
    sonidoGameOver.openFromFile("song/sonidoGameOver.ogg");
    Music winSong;
    Music etapaUno,etapaDos;
    etapaUno.openFromFile("song/etapaUno.ogg");
    etapaUno.setVolume(30);
    etapaDos.openFromFile("song/etapaDos.ogg");
    etapaDos.setVolume(30);
    winSong.openFromFile("song/winSong.ogg");
    winSong.setVolume(30);
    int juegoIniciado = 0;

    Fondo* fondo = nullptr;
    Aliado* simonecio = nullptr;
    sf::Texture maxianoTexture, brianTexture, klosterianoTexture;
    std::vector<Enemigo*> maxianos;
    std::vector<Enemigo*> brians;
    std::vector<Enemigo*> klosterianos;
    ContadorDeVida* vida = nullptr;
    ContadorDeVida* vidaKloster = nullptr;
    contadorDeEliminaciones* contador = nullptr;
    Cronometro* tiempo = nullptr;
    bool eliminacion = true;
    int contBrian = 0;
    int contMaxi = 0;
    bool gameOver = false;
    bool juegoGanado = false;
    sf::Font font;
    font.loadFromFile("font\\RETROTECH.ttf");


    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("PERDISTE MAKINOLA INTERGALACTICA\nPresiona ENTER para volver al menu");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getLocalBounds().width / 2.0f,
                             window.getSize().y / 2.0f - gameOverText.getLocalBounds().height / 2.0f);


// Configurar el texto WIN
    sf::Text winText;
    winText.setFont(font);
    winText.setString("FELICIDADES, LOGRASTE SALVAR LA UTN\nPresiona ENTER para volver al menu");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::Green);
    winText.setStyle(sf::Text::Bold);

// Centrar el texto en la ventana
    sf::FloatRect textBounds = winText.getLocalBounds();
    winText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    winText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    // Cargar la imagen del equipo
    sf::Texture textureEquipo;
    if (!textureEquipo.loadFromFile("img/fondoequipo.png"))
    {
        std::cerr << "No se pudo cargar la imagen" << std::endl;
        return -1;
    }
    sf::Sprite spriteEquipo(textureEquipo);
    spriteEquipo.setPosition(0, 0);


    music.play();
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (juegoIniciado == 0 && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.moverArriba();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    menu.moverAbajo();
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    int opcionSeleccionada = menu.mainMenuPresionar();
                    if (opcionSeleccionada == 0)
                    {
                        etapaUno.play();
                        juegoIniciado = 1;

                        limpiarJuego(fondo, simonecio, maxianos, brians, klosterianos, vida, vidaKloster, contador, tiempo);
                        inicializarJuego(window, fondo, simonecio, maxianoTexture, brianTexture, klosterianoTexture,
                                         maxianos, brians, klosterianos, vida, vidaKloster, contador, tiempo,
                                         eliminacion, contBrian, contMaxi);
                    }
                    else if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    {
                        music.stop();
                        gameOver = false;
                        juegoIniciado = 1;
                        limpiarJuego(fondo, simonecio, maxianos, brians, klosterianos, vida, vidaKloster, contador, tiempo);
                        inicializarJuego(window, fondo, simonecio, maxianoTexture, brianTexture, klosterianoTexture,
                                         maxianos, brians, klosterianos, vida, vidaKloster, contador, tiempo,
                                         eliminacion, contBrian, contMaxi);
                    }
                    else if (opcionSeleccionada == 1)
                    {
                        sf::Font font;

                        if (!font.loadFromFile("font\\RETROTECH.ttf"))
                        {
                            // Manejar error de carga de fuente
                            std::cerr << "No se pudo cargar la fuente." << std::endl;
                            continue;
                        }

                        ArchivoTiempo arcTiempo("tiempos.dat");
                        if (!arcTiempo.existeArchivo() || arcTiempo.contarRegistros() == 0)
                        {

                            sf::Text noTiemposText;
                            noTiemposText.setFont(font);
                            noTiemposText.setCharacterSize(45);
                            noTiemposText.setFillColor(sf::Color::Yellow);
                            noTiemposText.setString("No hay tiempos guardados .");
                            noTiemposText.setPosition(250, 350);

                            bool mostrarMensaje = true;

                            while (mostrarMensaje && window.isOpen())
                            {
                                while (window.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed)
                                    {
                                        window.close();
                                        mostrarMensaje = false;
                                    }
                                    else if (event.type == sf::Event::KeyPressed)
                                    {
                                        mostrarMensaje = false;
                                    }
                                }

                                window.clear();
                                window.draw(noTiemposText);
                                window.display();
                            }

                            continue;
                        }


                        int cantT = arcTiempo.contarRegistros();
                        std::vector<Tiempo> tiempos(cantT);

                        for (int i = 0; i < cantT; i++)
                        {
                            tiempos[i] = arcTiempo.leerRegistro(i);
                            std::sort(tiempos.begin(), tiempos.end(), [](const Tiempo& a, const Tiempo& b)
                        {
                            return a.getTiempo() < b.getTiempo();
                        });
                        }



                        std::vector<sf::Text> textos;
                        for (int i = 0; i < std::min(4, cantT); i++)
                        {

                            Tiempo guardar = tiempos[i];
                            std::ostringstream oss;
                            oss << std::fixed << std::setprecision(2) << guardar.getTiempo();
                            sf::Text text;
                            text.setFont(font);
                            text.setCharacterSize(45);
                            text.setFillColor(sf::Color::Yellow);
                            text.setString("Tiempo Record: " + oss.str() + " segundos");
                            text.setPosition(150, 150 * i + 150);
                            textos.push_back(text);
                        }


                        bool mostrarTiempos = true;
                        while (mostrarTiempos && window.isOpen())
                        {
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    window.close();
                                    mostrarTiempos = false;
                                }
                                else if (event.type == sf::Event::KeyPressed)
                                {

                                    mostrarTiempos = false;
                                }
                            }

                            window.clear();
                            for (const auto &text : textos)
                            {
                                window.draw(text);
                            }
                            window.display();
                        }
                    }

                    else if (opcionSeleccionada == 2)
                    {
                        window.clear();
                        window.draw(spriteEquipo);
                        window.display();
                        bool volverAlMenu = false;
                        while (!volverAlMenu)
                        {
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::KeyPressed)
                                {
                                    volverAlMenu = true;
                                    break;
                                }
                            }
                        }


                    }


                    else if (opcionSeleccionada == 3)
                    {
                        window.close();
                    }

                }

            }
        }

        window.clear();

        if (juegoIniciado == 1)
        {
            music.stop();
            fondo->draw(window);
            tiempo->dibujar(window);
            contador->draw(window);
            vida->dibujar(window);
            tiempo->actualizar();
            contador->actualizarTexto();
            simonecio->update();
            simonecio->draw(window);

            for (Enemigo* maxiano : maxianos)
            {
                maxiano->update();
                maxiano->draw(window);
            }
            for (Enemigo* brian : brians)
            {
                brian->update();
                brian->draw(window);
            }
            for (Enemigo* kloster : klosterianos)
            {
                kloster->update();
                kloster->draw(window);
            }

            if (gameOver)
            {
                window.draw(gameOverText);
            }

            std::vector<Bala*>& balas = simonecio->getVectorBalas();
            bool klosterEliminado = false;

            for (auto itKloster = klosterianos.begin(); itKloster != klosterianos.end();)
            {
                Enemigo* kloster = *itKloster;
                std::vector<Bomba*>& bombas = kloster->getVectorBombas();

                for (auto itBomba = bombas.begin(); itBomba != bombas.end();)
                {
                    Bomba* bomba = *itBomba;

                    if (simonecio->isCollision(*bomba))
                    {
                        delete bomba;
                        itBomba = bombas.erase(itBomba);
                        vida->disminuirVida(1);
                        sonidoColisionBomba.play();


                    }
                    else
                    {
                        ++itBomba;
                    }
                }

                if (!klosterEliminado)
                {
                    for (auto itBala = balas.begin(); itBala != balas.end();)
                    {
                        Bala* bala = *itBala;

                        if (kloster->isCollision(*bala))
                        {
                            delete bala;
                            itBala = balas.erase(itBala);
                            vidaKloster->disminuirVida(1);

                            if (vidaKloster->obtenerVida() == 0)
                            {
                                klosterEliminado = true;
                                break;
                            }
                        }
                        else
                        {
                            ++itBala;
                        }
                    }
                }

                if (klosterEliminado)
                {
                    delete kloster;
                    itKloster = klosterianos.erase(itKloster);
                }
                else
                {
                    ++itKloster;
                }
            }

            if (contBrian == 15 && contMaxi == 15)
            {
                etapaUno.stop();
                etapaDos.play();
                eliminacion = false;

                sf::Vector2f randomPosition = sf::Vector2f(
                                                  std::rand() % (window.getSize().x - klosterianoTexture.getSize().x),
                                                  std::rand() % (window.getSize().y - klosterianoTexture.getSize().y)
                                              );
                Enemigo* newKlosteriano = new Enemigo(2, klosterianoTexture, randomPosition);
                newKlosteriano->setScale(1.8, 1.8);
                newKlosteriano->setVelocidad(10, 10);
                klosterianos.emplace_back(newKlosteriano);
                contBrian = 0;
                contMaxi = 0;

                klosterBns.play();
            }

            if (!eliminacion)
            {
                vidaKloster->posicionVida(10, 10, window);
            }

            if (maxianos.empty() && brians.empty() && eliminacion)
            {
                for (int i = 0; i < 5; ++i)
                {
                    sf::Vector2f randomPositionMaxiano = sf::Vector2f(
                            std::rand() % (window.getSize().x - maxianoTexture.getSize().x),
                            std::rand() % (window.getSize().y - maxianoTexture.getSize().y)
                                                         );
                    maxianos.emplace_back(new Enemigo(1, maxianoTexture, randomPositionMaxiano));

                    sf::Vector2f randomPositionBrian = sf::Vector2f(
                                                           std::rand() % (window.getSize().x - brianTexture.getSize().x),
                                                           std::rand() % (window.getSize().y - brianTexture.getSize().y)
                                                       );
                    brians.emplace_back(new Enemigo(1, brianTexture, randomPositionBrian));
                }
            }

            if (vida->obtenerVida() == 0 || (vidaKloster && vidaKloster->obtenerVida() == 0))
            {
                etapaDos.stop();


                if (vida->obtenerVida() == 0)
                {
                    gameOver = true;
                    sonidoGameOver.play();
                    if (vida == 0)
                    {
                        etapaDos.stop();
                    }
                    etapaUno.stop();
                    etapaDos.stop();

                    window.draw(gameOverText);
                    window.display();


                    bool esperaEnter = true;
                    while (esperaEnter && window.isOpen())
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                            {
                                window.close();
                                esperaEnter = false;
                            }
                            else if (event.type == sf::Event::KeyPressed)
                            {
                                if (event.key.code == sf::Keyboard::Enter)
                                {
                                    gameOver = false;
                                    esperaEnter = false;
                                    sonidoGameOver.stop();
                                }
                            }
                        }



                        window.clear();
                        window.draw(gameOverText);
                        window.display();
                    }
                }


                if (vidaKloster->obtenerVida() == 0)
                {
                    etapaDos.stop();
                    klosterEliminado = true;
                    tiempo->detener();
                    ArchivoTiempo archivoTiempo("tiempos.dat");
                    float tiempoTranscurrido = tiempo->obtenerTiempoTranscurrido();
                    float tiempoRedondeado = round(tiempoTranscurrido * 100.0f) / 100.0f;
                    Tiempo transcurrido(tiempoRedondeado);
                    archivoTiempo.grabarRegistro(transcurrido);
                    juegoGanado = true;
                    winSong.play();

                }


                juegoIniciado = 0;

                inicializarJuego(window, fondo, simonecio, maxianoTexture, brianTexture, klosterianoTexture,
                                 maxianos, brians, klosterianos, vida, vidaKloster, contador, tiempo, eliminacion,
                                 contBrian, contMaxi);
                menu.dibujar(window);
            }

            if (juegoGanado)
            {
                // Dibuja el texto de WIN
                window.clear();
                window.draw(winText);
                window.display();


                bool esperaEnter = true;
                while (esperaEnter && window.isOpen())
                {
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            window.close();
                            esperaEnter = false;
                        }
                        else if (event.type == sf::Event::KeyPressed)
                        {
                            if (event.key.code == sf::Keyboard::Enter)
                            {
                                juegoGanado = false;
                                esperaEnter = false;
                            }
                        }
                    }

                    window.clear();
                    window.draw(winText);
                    window.display();
                }
            }
            for (auto itMaxiano = maxianos.begin(); itMaxiano != maxianos.end();)
            {
                Enemigo* maxi = *itMaxiano;
                bool colision = false;

                for (auto itBala = balas.begin(); itBala != balas.end();)
                {
                    Bala* disparo = *itBala;

                    if (maxi->isCollision(*disparo))
                    {
                        delete disparo;
                        itBala = balas.erase(itBala);
                        colision = true;
                    }
                    else
                    {
                        ++itBala;
                    }
                }

                if (colision)
                {
                    delete maxi;
                    itMaxiano = maxianos.erase(itMaxiano);
                    contador->contadorMaxianos();
                    contMaxi++;
                }
                else
                {
                    ++itMaxiano;
                }
            }

            for (auto itBrian = brians.begin(); itBrian != brians.end();)
            {
                Enemigo* brian = *itBrian;
                bool colision = false;

                for (auto itBala = balas.begin(); itBala != balas.end();)
                {
                    Bala* disparo = *itBala;

                    if (brian->isCollision(*disparo))
                    {
                        delete disparo;
                        itBala = balas.erase(itBala);
                        delete brian;
                        itBrian = brians.erase(itBrian);
                        colision = true;
                        contador->contadorBrians();
                        contBrian++;
                    }
                    else
                    {
                        ++itBala;
                    }
                }

                if (!colision)
                {
                    ++itBrian;
                }
            }

            for (auto& maxiano : maxianos)
            {
                std::vector<Bomba*>& bombas = maxiano->getVectorBombas();

                for (auto itBomba = bombas.begin(); itBomba != bombas.end();)
                {
                    Bomba* bomba = *itBomba;

                    if (simonecio->isCollision(*bomba))
                    {
                        delete bomba;
                        itBomba = bombas.erase(itBomba);
                        vida->disminuirVida(1);

                        sonidoColisionBomba.play();

                    }
                    else
                    {
                        ++itBomba;
                    }
                }
            }

            for (auto& brian : brians)
            {
                std::vector<Bomba*>& bombas = brian->getVectorBombas();

                for (auto itBomba = bombas.begin(); itBomba != bombas.end();)
                {
                    Bomba* bomba = *itBomba;

                    if (simonecio->isCollision(*bomba))
                    {
                        delete bomba;
                        itBomba = bombas.erase(itBomba);
                        vida->disminuirVida(1);

                        sonidoColisionBomba.play();
                    }
                    else
                    {
                        ++itBomba;
                    }
                }
            }



            tiempo->iniciar();
        }
        else
        {
            menu.dibujar(window);
            winSong.stop();
        }

        window.display();
    }




    return 0;
}

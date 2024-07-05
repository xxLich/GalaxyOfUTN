#ifndef ARCHPUNTOS_H_INCLUDED
#define ARCHPUNTOS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cmath>

class Tiempo {
public:
    Tiempo();
    Tiempo(float tiempo);

    float getTiempo() const;
    void setTiempo(float tiempo);
    float obtenerSoloSegundos() const;

private:
    float _tiempo;
};

class ArchivoTiempo {
public:
    ArchivoTiempo(const char *n);
    Tiempo leerRegistro(int pos);
    int contarRegistros();
    bool grabarRegistro(Tiempo reg);
     bool existeArchivo();

private:
    char nombre[100];
};

#endif // ARCHPUNTOS_H_INCLUDED

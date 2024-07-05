#include "archPuntos.h"
#include <cstring>
#include <cstdio>
#include <cmath>

// Definiciones de la clase Tiempo
Tiempo::Tiempo() : _tiempo(0.0f) {}

Tiempo::Tiempo(float tiempo) : _tiempo(tiempo) {}

float Tiempo::getTiempo() const {
    return _tiempo;
}

void Tiempo::setTiempo(float tiempo) {
    _tiempo = tiempo;
}

float Tiempo::obtenerSoloSegundos() const {
    return (int)_tiempo; // Devuelve solo la parte entera de los segundos
}

// Definiciones de la clase ArchivoTiempo
ArchivoTiempo::ArchivoTiempo(const char *n) {
    strncpy(nombre, n, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
}

Tiempo ArchivoTiempo::leerRegistro(int pos) {
    Tiempo reg;
    FILE *p = fopen("tiempos.dat", "rb");
    if (p == NULL) {
        std::cerr << "Error al abrir el archivo para lectura" << std::endl;
        return reg;
    }
    fseek(p, pos * sizeof(reg), SEEK_SET);
    fread(&reg, sizeof(reg), 1, p);
    fclose(p);
    return reg;
}

int ArchivoTiempo::contarRegistros() {
    FILE *p = fopen("tiempos.dat", "rb");
    if (p == NULL) {
        std::cerr << "Error al abrir el archivo para lectura" << std::endl;
        return -1;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Tiempo);
    fclose(p);
    return cant;
}

bool ArchivoTiempo::grabarRegistro(Tiempo reg) {
    FILE *p = fopen("tiempos.dat", "ab");
    if (p == NULL) {
        std::cerr << "Error al abrir el archivo para escritura" << std::endl;
        return false;
    }
    size_t escribio = fwrite(&reg, sizeof(reg), 1, p);
    fclose(p);
    return escribio == 1;
}

bool ArchivoTiempo::existeArchivo() {
    std::ifstream file(nombre);
    return file.good(); // Devuelve true si se puede abrir el archivo para lectura
}

#ifndef ARCHIVO_H
#define ARCHIVO_H
#include "pila.h"
#include "ocurrencia.h"

class Archivo
{
private:
    char* path;
    char* nombre;
    char** lines;
    int cantLines=0;

public:
    Archivo();
    Ocurrencia* ocurrencia;

    void setPath(char* path);
    char* getPath();

    void setNombre(char* nombre);
    char* getNombre();

    int getCantidadCaracteres();

    char** getLines(char *path, bool isOcurrencia = false);
    void addLine(char* line);

    int getCantLines();

};

#endif // ARCHIVO_H

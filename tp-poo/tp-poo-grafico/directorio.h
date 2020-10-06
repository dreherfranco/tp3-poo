#ifndef DIRECTORIO_H
#define DIRECTORIO_H

#include <iostream>
//Libreria para manejar directorios
#include <dirent.h>
#include <string.h>
#include "QList"

class Directorio
{
private:
    char** archivos;
    int cantArchivos = 0;
public:
    Directorio();

    void setListaArchivos(const char* directorio);
    char** getArchivos();

    void addArchivo(char* file);

    bool isTXT(char* nombreArchivo, char* extension);
    int getCantArchivos();
};

#endif // DIRECTORIO_H

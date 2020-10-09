#ifndef ARCHIVO_H
#define ARCHIVO_H
//#include "gestorarchivoocurrencias.h"
#include "ocurrencia.h"
#include "ArchivoStruct.h"

class Archivo
{
private:
    char* path;
    char* nombre;
    char** lines;
    int cantLines=0;
    int totalOcurrencias;
public:
    Archivo();
    Ocurrencia* ocurrencia;

    void setPath(char* path);
    void setPath(ArchivoStruct archivo);
    char* getPath();
    void setTotalOcurrencias(int total);

    void setNombre(char* nombre);
    void setNombre(ArchivoStruct archivo);
    char* getNombre();

    int getCantidadCaracteres();

    char** getLines(char *path, bool isOcurrencia = false);
    void addLine(char* line);

    int getCantLines();

};

#endif // ARCHIVO_H

#ifndef DIRECTORIO_H
#define DIRECTORIO_H

#include <iostream>
//Libreria para manejar directorios
#include <dirent.h>
#include "QList"
#include "vector"

class Directorio
{
private:
    QStringList archivos;
public:
    Directorio(std::string directorio);

    void setDirectorio(std::string directorio);
    QStringList getArchivos();

    void addArchivo(QString file);

    bool isTXT(std::string nombreArchivo, std::string extension);
    int getCantArchivos();
};


#endif // DIRECTORIO_H

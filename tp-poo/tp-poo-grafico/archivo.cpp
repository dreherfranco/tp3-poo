#include "archivo.h"
#include <iostream>
#include <fstream>
#include "string.h"
#include <string>


Archivo::Archivo()
{
    this->lines = nullptr;
    this->path = nullptr;
    this->ocurrencia = new Ocurrencia();
    this->nombre=nullptr;
}


void Archivo::setPath(char *path)
{
    delete[] this->path;
    this->path = path;
}

void Archivo::setPath(ArchivoStruct archivo)
{
    int tamanio = strlen(archivo.path);
    this->path = new char[tamanio+1];
    strcpy(this->path, archivo.path);
}

char *Archivo::getPath()
{
    return this->path;
}

void Archivo::setTotalOcurrencias(int total)
{
    this->totalOcurrencias = total;
}

void Archivo::setNombre(char *nombre)
{
    this->nombre = nombre;
}

void Archivo::setNombre(ArchivoStruct archivo)
{
    int tamanio = strlen(archivo.nombre);
    this->nombre = new char[tamanio+1];
    strcpy(this->nombre, archivo.nombre);
}

char *Archivo::getNombre()
{
    return this->nombre;
}

int Archivo::getCantidadCaracteres()
{
    std::ifstream archivo;
    char buffer;
    int cont=0;

    archivo.open(this->path);

    //Cuenta tambien los saltos de lineas \n
    while(!archivo.eof()){
        archivo.get(buffer);
        cont++;
    }

    archivo.close();
    return cont;
}


//Obtener todas las lineas que contiene el archivo
char** Archivo::getLines(char *path){
    std::ifstream archivo;
    int linea = 0;
    int longitudLinea;
    std::string buffer;

    archivo.open(path);

    while(!archivo.eof()){
        //Obtengo la linea del archivo
        getline(archivo, buffer);
        //Longitud de los caracteres de la linea
        longitudLinea = buffer.length();

        char* line = nullptr;
        line = new char[longitudLinea+1];
        strcpy(line, buffer.c_str());

        //Agrego una linea del archivo por cada iteracion a this->lines
        addLine(line);
        }

    //Devuelve todas las lineas del archivo
    return this->lines;
}

//Agregar una linea a this->lines la cual se va a usar para sacar las lineas del archivo en la GUI
void Archivo::addLine(char *line)
{
    char** aux = new char*[this->cantLines+1];

    for(int i=0; i<this->cantLines; i++){
        aux[i] = this->lines[i];
    }

    aux[this->cantLines] = line;
    delete[] this->lines;
    this->lines = aux;
    this->cantLines++;
}

int Archivo::getCantLines()
{
    return cantLines;
}

void Archivo::setearOcurrencias(char *path)
{
    std::ifstream archivo;
    int posicionLinea = 0;
    int longitudLinea;
    std::string buffer;

    archivo.open(path);

    while(!archivo.eof()){
        //Obtengo la linea del archivo
        getline(archivo, buffer);
        //Longitud de los caracteres de la linea
        longitudLinea = buffer.length();

        char* line = nullptr;
        line = new char[longitudLinea+1];
        strcpy(line, buffer.c_str());

        //cuenta la linea en la que se encuentra
        posicionLinea++;
        //Cuenta las ocurrencias por cada linea del archivo
        this->ocurrencia->contOcurrencia(line, posicionLinea, nombre);
    }
}



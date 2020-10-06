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

char *Archivo::getPath()
{
    return this->path;
}

void Archivo::setNombre(char *nombre)
{
    this->nombre = nombre;
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
char** Archivo::getLines(char *path, bool isOcurrencia){
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
        //Asigno memoria a buffer, esta almacenara la linea, +1 que es el salto de linea
        line = new char[longitudLinea+1];
        //Copio lo que hay en el string line en buffer
        strcpy(line, buffer.c_str());

        if(isOcurrencia){
            //cuenta la linea en la que se encuentra
            linea++;
            //Cuenta las ocurrencias por cada linea del archivo
            this->ocurrencia->contOcurrencia(line, linea);

        }else{

        //Agrego una linea a la propiedad del objeto this->lines
        addLine(line);
        }
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



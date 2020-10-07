#include "pila.h"
#include <fstream>
#include "string.h"

Pila::Pila()
{
    this->pila = new NodoP;
    this->pila = NULL;
    this->cantNodos=0;
}

void Pila::add(int posOcurrencia, int linea, char* file)
{
    /*
    NodoP* nuevo_nodo = new NodoP;
    //Asigno los valores que contendran los nodos
    nuevo_nodo->posicionOcu = posOcurrencia;
    nuevo_nodo->linea = linea;

    if(pila == NULL){
        nuevo_nodo->sig = NULL;
    }else{
        nuevo_nodo->sig = pila;
    }

    pila = nuevo_nodo;
    */
    //this->setNombreArchivo(file);

    std::ofstream archivo("ocurrencias.dat",std::ios::binary | std::ios::out | std::ios::ate);
    ocurrenciaStruct ocuStruct;

    ocuStruct.pos = posOcurrencia;
    ocuStruct.linea = linea;
    strcpy(ocuStruct.nombreArch, file);
    archivo.write((char*)&ocuStruct, sizeof (ocuStruct));

    archivo.close();
}

std::vector<ocurrenciaStruct> Pila::getLinea_y_Pos()
{
    std::ifstream file("ocurrencias.dat", std::ios::binary);
     ocurrenciaStruct ocuStruct;
    std::vector<ocurrenciaStruct> vectorOcs;

    while(!file.eof()){
        file.read((char*)&ocuStruct, sizeof (ocuStruct));

        if(!file.eof()){
            if(ocuStruct.nombreArch == this->nombreArchivo ){
                vectorOcs.push_back(ocuStruct);
            }
        }
    }
    return vectorOcs;
}

int Pila::getCantNodos()
{
    std::ifstream file("ocurrencias.dat", std::ios::binary);
     ocurrenciaStruct ocuStruct;
     int cont=0;

    while(!file.eof()){
        file.read((char*)&ocuStruct, sizeof (ocuStruct));

        if(!file.eof()){
            if(ocuStruct.nombreArch == this->nombreArchivo ){
                ++cont;
            }
        }
    }
    return cont;
}

void Pila::setCantNodos(int cantNodos)
{
    this->cantNodos += cantNodos;
}

void Pila::setNombreArchivo(char *nombre)
{
    this->nombreArchivo = nombre;
}

#ifndef OCURRENCIA_H
#define OCURRENCIA_H
#include "pila.h"

class Ocurrencia
{
private:
    char* ocurrencia;
    int tamanioOcu;

    //Donde se guardan las ocurrencias con sus posiciones y la cantidad de ocurrencias encontradas
    Pila* pila;
    NodoP* nodo;

public:
    Ocurrencia();
    void contOcurrencia(char* lineaArchivo, int linea);

    char *getOcurrencia();
    void setOcurrencia(char* ocu);

    void setTamanioOcu(int tamanio);

    int getCantOcurrencias();

    int* getLinea_yPos();

    int getCantNodos();
};

#endif // OCURRENCIA_H

#ifndef OCURRENCIA_H
#define OCURRENCIA_H
#include "pila.h"
#include "ArchivoStruct.h"

class Ocurrencia
{
private:
    char* ocurrencia;
    int tamanioOcu;
    int totalOcurrencias;
    //Donde se guardan las ocurrencias con sus posiciones y la cantidad de ocurrencias encontradas
    Pila* pila;
    NodoP* nodo;

public:
    Ocurrencia();
    void contOcurrencia(char* lineaArchivo, int linea, char* file);

    char *getOcurrencia();
    void setOcurrencia(char* ocu);
    void setOcurrencia(ArchivoStruct archivo);
    void setTamanioOcu(int tamanio);
    void setTotalOcurrencias(int total);

    int getCantOcurrencias();

    std::vector<ocurrenciaStruct> getLinea_yPos(char* nombreArchivo);
    void setNombreArchivo(char* file);
    int getCantNodos();
    void addBinario();
};

#endif // OCURRENCIA_H

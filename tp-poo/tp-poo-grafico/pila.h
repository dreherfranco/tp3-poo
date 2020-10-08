#ifndef PILA_H
#define PILA_H
#include <iostream>
#include "vector"

struct NodoP{
    int posicionOcu;
    int linea;
    char ocurrencia[60];
    char nombreArch[60];
    NodoP* sig;
};

struct ocurrenciaStruct{
    int linea;
    int pos;
    char nombreArch[60];
    char ocurrencia[60];
};

class Pila
{
private:
    NodoP* pila;
    int cantNodos=0;
    char* nombreArchivo;
public:
    Pila();
    void add(int posOcurrencia, int linea,char* file, char* ocurrencia);
    std::vector<ocurrenciaStruct> getLinea_y_Pos(char* ocurrencia,char* nombreArchivo);
    int getCantNodos();
    void setCantNodos(int cantNodos);
    void setNombreArchivo(char* nombre);
    void addBinario();
};

#endif // PILA_H

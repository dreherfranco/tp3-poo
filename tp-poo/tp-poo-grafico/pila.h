#ifndef PILA_H
#define PILA_H
#include <iostream>
#include "vector"

struct NodoP{
    int posicionOcu;
    int linea;
    NodoP* sig;
};

struct ocurrenciaStruct{
    int linea;
    int pos;
    char nombreArch[60];
};

class Pila
{
private:
    NodoP* pila;
    int cantNodos=0;
    char* nombreArchivo;
public:
    Pila();
    void add(int posOcurrencia, int linea,char* file);
    std::vector<ocurrenciaStruct> getLinea_y_Pos();
    int getCantNodos();
    void setCantNodos(int cantNodos);
    void setNombreArchivo(char* nombre);
};

#endif // PILA_H

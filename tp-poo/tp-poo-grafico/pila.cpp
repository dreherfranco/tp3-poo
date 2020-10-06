#include "pila.h"
#include <iostream>

Pila::Pila()
{
    this->pila = new NodoP;
    this->pila = NULL;
    this->cantNodos=0;
}

void Pila::add(int posOcurrencia, int linea)
{
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
}

int *Pila::getLinea_y_Pos()
{
    int* aux = new int[2];
    NodoP* nodoAux = pila;
    //la posicion 0 del arreglo sera la posicion
    aux[0] = nodoAux->posicionOcu;
    //la posicion 1 sera la linea donde se encuentra la ocurrencia
    aux[1] = nodoAux->linea;
    pila = pila->sig;
    delete nodoAux;
    return aux;
}

int Pila::getCantNodos()
{
    return this->cantNodos;
}

void Pila::setCantNodos(int cantNodos)
{
    this->cantNodos += cantNodos;
}

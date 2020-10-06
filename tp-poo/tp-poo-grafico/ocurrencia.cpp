#include "ocurrencia.h"
#include <iostream>

Ocurrencia::Ocurrencia()
{
    this->pila = new Pila();
    this->nodo = new NodoP;
    this->nodo = NULL;
}
void Ocurrencia::contOcurrencia(char* lineaArchivo, int linea)
{
    int cuentaOcurrencia = 0;
    int j = 0;
    int i=0;

    while(lineaArchivo[i] != '\0'){

        while(this->ocurrencia[j] == lineaArchivo[i]){
            // Se le restan 1 por la longitud del arreglo, ya que este empieza a contar en 0
            if(j == tamanioOcu-1){

                //Cuenta la ocurrencia una vez que la cantidad del vector sea igual al valor que haya acumulado j
                cuentaOcurrencia++;

                //Agrego una ocurrencia a la pila con su posicion i donde se encuentra en el archivo de texto, y la linea
                //********************//
                this->pila->add(i-tamanioOcu+1, linea);
                //*******************//

            }
            j++;
            //la variable i tendra que ir a la par de j para comparar en la siguiente iteracion
            i++;
        }

        //se reinicia a 0 para volver a comprobar si hay ocurrencias una vez que termine la estructura while
        j=0;
        //contador del primer while
        i++;
    }
    //Setea la cantidad de nodos que tiene la pila
    this->pila->setCantNodos(cuentaOcurrencia);
}

void Ocurrencia::setOcurrencia(char *ocu){
    this->ocurrencia = ocu;
}

void Ocurrencia::setTamanioOcu(int tamanio)
{
    tamanioOcu = tamanio;
}

int Ocurrencia::getCantOcurrencias()
{
    return pila->getCantNodos();
}

int *Ocurrencia::getLinea_yPos()
{
    return this->pila->getLinea_y_Pos();
}

int Ocurrencia::getCantNodos()
{
    return pila->getCantNodos();
}

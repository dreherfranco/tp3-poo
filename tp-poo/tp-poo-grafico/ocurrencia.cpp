#include "ocurrencia.h"
#include <iostream>
#include "string.h"

Ocurrencia::Ocurrencia()
{
    this->gestor = new GestorArchivoOcurrencias();

}
void Ocurrencia::contOcurrencia(char* lineaArchivo, int linea, char* file)
{
    int cuentaOcurrencia = 0;
    int j = 0;
    int i=0;
    bool band = false;

    while(lineaArchivo[i] != '\0'){

        while(this->ocurrencia[j] == lineaArchivo[i]){
            // Se le restan 1 por la longitud del arreglo, ya que este empieza a contar en 0
            if(j == tamanioOcu-1){

                //Cuenta la ocurrencia una vez que la cantidad del vector sea igual al valor que haya acumulado j
                cuentaOcurrencia++;

                //Agrego una ocurrencia a la pila con su posicion i donde se encuentra en el archivo de texto, y la linea
                //********************//
                this->gestor->add(i-tamanioOcu+1, linea, file, this->ocurrencia);
                //*******************//
                band = true;
            }

            j++;
            //la variable i tendra que ir a la par de j para comparar en la siguiente iteracion
            if(!band)
                i++;
            else
                band = false;

        }

        //se reinicia a 0 para volver a comprobar si hay ocurrencias una vez que termine la estructura while
        j=0;
        //contador del primer while
        i++;
    }
    //Setea la cantidad de nodos que tiene la pila
    this->gestor->setCantNodos(cuentaOcurrencia);
}

char *Ocurrencia::getOcurrencia()
{
    return ocurrencia;
}

void Ocurrencia::setOcurrencia(char *ocu){
    this->ocurrencia = ocu;
}

void Ocurrencia::setOcurrencia(ArchivoStruct archivo)
{
    int tamanio = strlen(archivo.ocurrencia);
    this->ocurrencia = new char[tamanio+1];
    strcpy(this->ocurrencia, archivo.ocurrencia);
}

void Ocurrencia::setTamanioOcu(int tamanio)
{
    tamanioOcu = tamanio;
}

void Ocurrencia::setTotalOcurrencias(int total)
{
    this->totalOcurrencias = total;
}

int Ocurrencia::getCantOcurrencias()
{
    return totalOcurrencias;
}

std::vector<ocurrenciaStruct> Ocurrencia::getLinea_yPos(char* nombreArchivo)
{
    return this->gestor->getLinea_y_Pos(this->ocurrencia, nombreArchivo);
}

void Ocurrencia::setNombreArchivo(char *file)
{
    this->gestor->setNombreArchivo(file);
}

int Ocurrencia::getCantNodos()
{
    return gestor->getCantNodos();
}


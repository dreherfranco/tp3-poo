#include "pila.h"
#include <fstream>
#include "string.h"

Pila::Pila()
{
    this->pila = new NodoP;
    this->pila = NULL;
    this->cantNodos=0;
}

void Pila::add(int posOcurrencia, int linea, char* file,char* ocurrencia)
{
   /* std::ofstream archivo;
    ocurrenciaStruct ocuStruct;
    archivo.open("ocurrencias.dat",std::ios::binary | std::ios::out | std::ios::ate);

    ocuStruct.pos = posOcurrencia;
    ocuStruct.linea = linea;
    strcpy(ocuStruct.ocurrencia, ocurrencia);
    strcpy(ocuStruct.nombreArch, file);
    archivo.write((char*)&ocuStruct, sizeof (ocuStruct));

    archivo.close();
    */
    NodoP* nuevo_nodo = new NodoP;
        //Asigno los valores que contendran los nodos
        nuevo_nodo->posicionOcu = posOcurrencia;
        nuevo_nodo->linea = linea;
        strcpy(nuevo_nodo->ocurrencia, ocurrencia);
        strcpy(nuevo_nodo->nombreArch,file);
        if(pila == NULL){
            nuevo_nodo->sig = NULL;
        }else{
            nuevo_nodo->sig = pila;
        }

        pila = nuevo_nodo;
}

std::vector<ocurrenciaStruct> Pila::getLinea_y_Pos(char* ocurrencia, char* nombreArchivo)
{
    std::ifstream file("ocurrencias.dat", std::ios::binary);
     ocurrenciaStruct ocuStruct;
    std::vector<ocurrenciaStruct> vectorOcs;

    while(!file.eof()){
        file.read((char*)&ocuStruct, sizeof (ocuStruct));

        if(!file.eof()){
            if(strcmp(ocuStruct.nombreArch , nombreArchivo)==0 && strcmp(ocuStruct.ocurrencia, ocurrencia)){
                vectorOcs.push_back(ocuStruct);
            }
        }
    }
    return vectorOcs;
}

int Pila::getCantNodos()
{
    return cantNodos;
}

void Pila::setCantNodos(int cantNodos)
{
    this->cantNodos += cantNodos;
}

void Pila::setNombreArchivo(char *nombre)
{
    this->nombreArchivo = nombre;
}

void Pila::addBinario()
{
    std::ofstream archivo;
    ocurrenciaStruct ocuStruct;
    archivo.open("ocurrencias.dat",std::ios::binary | std::ios::out | std::ios::ate);

     while(pila != NULL){
         NodoP* nodoAux = pila;
        ocuStruct.pos = nodoAux->posicionOcu;
        ocuStruct.linea = nodoAux->linea;
        strcpy(ocuStruct.ocurrencia,nodoAux->ocurrencia);
        strcpy(ocuStruct.nombreArch, nodoAux->nombreArch);

        archivo.seekp(0,std::ios::beg);
        archivo.write((char*)&ocuStruct, sizeof (ocuStruct));
        pila = pila->sig;
        delete nodoAux;
    }
    archivo.close();
}

#include "pila.h"
#include <fstream>
#include "string.h"

Pila::Pila()
{
    this->pila = new NodoP;
    this->pila = NULL;
    this->cantNodos=0;
}

/*void Pila::add(int posOcurrencia, int linea, char* file,char* ocurrencia)
{
    std::ofstream archivo;
    ocurrenciaStruct ocuStruct;
    archivo.open("ocurrencias.dat",std::ios::binary | std::ios::out | std::ios::app);

    ocuStruct.pos = posOcurrencia;
    ocuStruct.linea = linea;
    strcpy(ocuStruct.ocurrencia, ocurrencia);
    strcpy(ocuStruct.nombreArch, file);
    archivo.write((char*)&ocuStruct, sizeof (ocuStruct));

    archivo.close();
}

std::vector<ocurrenciaStruct> Pila::getLinea_y_Pos(char* ocurrencia, char* nombreArchivo)
{
    std::ifstream file("ocurrencias.dat", std::ios::binary | std::ios::in );
     ocurrenciaStruct ocuStruct;
    std::vector<ocurrenciaStruct> vectorOcs;

    while(file.read((char*)&ocuStruct, sizeof (ocuStruct))){
            if(strcmp(ocuStruct.nombreArch , nombreArchivo)==0 && strcmp(ocuStruct.ocurrencia, ocurrencia)==0){
                vectorOcs.push_back(ocuStruct);
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
}*/

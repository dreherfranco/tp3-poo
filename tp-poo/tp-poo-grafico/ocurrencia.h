#ifndef OCURRENCIA_H
#define OCURRENCIA_H
//#include "pila.h"
#include "ArchivoStruct.h"
//#include "gestorarchivoocurrencias.h"
#include "vector"
#include "ocurrenciaStruct.h"

class Ocurrencia
{
private:
    char* ocurrencia;
    char* nombreArchivo;
    int tamanioOcu;
    int totalOcurrencias;
    //Donde se guardan las ocurrencias con sus posiciones y la cantidad de ocurrencias encontradas
    //GestorArchivoOcurrencias* gestor;

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
    void setNombreArchivo(char* nombre);
    int getCantNodos();
    void add_aBinario(int posOcurrencia, int linea, char* file);
};

#endif // OCURRENCIA_H

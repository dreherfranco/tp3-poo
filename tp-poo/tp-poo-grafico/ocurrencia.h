#ifndef OCURRENCIA_H
#define OCURRENCIA_H
#include "ArchivoStruct.h"
#include "vector"
#include "ocurrenciaStruct.h"

class Ocurrencia
{
private:
    char* ocurrencia;
    char* nombreArchivo;
    int tamanioOcu;
    int totalOcurrencias;
    char* rutaArchivoBinario;

public:
    Ocurrencia();
    void contOcurrencia(char* lineaArchivo, int linea, char* file);

    char *getOcurrencia();
    void setOcurrencia(char* ocu);
    //Necesario para guardar en binario
    void setOcurrencia(ArchivoStruct archivo);

    void setTamanioOcu(int tamanio);
    void setTotalOcurrencias(int total);
    int getTotalOcurrencias();
    void setRutaArchivoBinario(char* path);
    std::vector<ocurrenciaStruct> getLinea_yPos(char* nombreArchivo);
    void setNombreArchivo(char* nombre);
    void add_aBinario(int posOcurrencia, int linea, char* file);
    void actualizarBinarioOcurrencias();
};

#endif // OCURRENCIA_H

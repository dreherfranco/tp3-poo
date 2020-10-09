#include "gestorarchivoocurrencias.h"
#include "string.h"
#include "fstream"

GestorArchivoOcurrencias::GestorArchivoOcurrencias()
{

}

void GestorArchivoOcurrencias::add(int posOcurrencia, int linea, char* file,char* ocurrencia)
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

std::vector<ocurrenciaStruct> GestorArchivoOcurrencias::getLinea_y_Pos(char* ocurrencia, char* nombreArchivo)
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

int GestorArchivoOcurrencias::getCantNodos()
{
    return cantNodos;
}

void GestorArchivoOcurrencias::setCantNodos(int cantNodos)
{
    this->cantNodos += cantNodos;
}

void GestorArchivoOcurrencias::setNombreArchivo(char *nombre)
{
    this->nombreArchivo = nombre;
}

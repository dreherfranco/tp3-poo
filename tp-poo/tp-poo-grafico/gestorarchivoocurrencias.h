#ifndef GESTORARCHIVOOCURRENCIAS_H
#define GESTORARCHIVOOCURRENCIAS_H
#include "vector"

struct ocurrenciaStruct{
    int linea;
    int pos;
    char nombreArch[60];
    char ocurrencia[60];
};

class GestorArchivoOcurrencias
{
private:
    int cantNodos=0;
    char* nombreArchivo;
public:
    void add(int posOcurrencia, int linea,char* file, char* ocurrencia);
    std::vector<ocurrenciaStruct> getLinea_y_Pos(char* ocurrencia,char* nombreArchivo);
    int getCantNodos();
    void setCantNodos(int cantNodos);
    void setNombreArchivo(char* nombre);

    GestorArchivoOcurrencias();
};

#endif // GESTORARCHIVOOCURRENCIAS_H

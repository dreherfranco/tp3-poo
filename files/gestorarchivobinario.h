#ifndef GESTORARCHIVOBINARIO_H
#define GESTORARCHIVOBINARIO_H
#include "string"
#include "vector"
#include "fstream"
#include "StructIndice.h"
#include "archivo.h"
#include "map"

class GestorArchivoBinario
{
public:
    GestorArchivoBinario();
    void crearIndice(std::string directorio,std::vector<Archivo> vectorConStructDeIndices);
    void actualizarIndice(std::string directorio,  std::vector<Archivo> vectorConStructDeIndices);
    std::vector<structInd> leerArchivo(std::string directorio, std::string ocurrencia="");
    std::vector<structInd> leerTodoElContenidoDelArchivo(std::string directorio);
    std::vector<structInd> leerArchivoPorOcurrencia(std::string directorio, std::string ocurrencia);
};

#endif // GESTORARCHIVOBINARIO_H

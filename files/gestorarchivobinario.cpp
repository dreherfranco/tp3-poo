#include "gestorarchivobinario.h"

GestorArchivoBinario::GestorArchivoBinario()
{

}

void GestorArchivoBinario::crearIndice(std::string directorio, std::vector<Archivo> archivos)
{
    std::string nombreArchivoBinario = directorio + "\\Indice.dat";
    std::ofstream archivoBinario(nombreArchivoBinario,std::ios::binary | std::ios::out | std::ios::app);

    Archivo archivoIterador;
    structInd indiceStruct;
    std::map<std::string,int> obtenerIndices;

    for(auto it = archivos.begin(); it != archivos.end(); ++it){
        archivoIterador =  *it;
        obtenerIndices = archivoIterador.getIndices();
        for(auto ind = obtenerIndices.begin(); ind != obtenerIndices.end(); ++ind){
            strcpy(indiceStruct.NombreArchivo, archivoIterador.getName().c_str());
            //palabra
            strcpy(indiceStruct.palabra, (*ind).first.c_str());
            //cantidad de veces encontrada
            indiceStruct.cantOcu = (*ind).second;
            archivoBinario.write((char*)&indiceStruct, sizeof(indiceStruct));
        }
    }
    archivoBinario.close();

}

void GestorArchivoBinario::actualizarIndice(std::string directorio,  std::vector<Archivo> archivos)
{
    std::string nombreArchivoBinario = directorio + "\\Indice.dat";
    std::ofstream archivoBinario(nombreArchivoBinario,std::ios::binary | std::ios::out | std::ios::trunc );
    Archivo archivoIterador;
    structInd indiceStruct;
    std::map<std::string,int> obtenerIndices;

    for(auto it = archivos.begin(); it != archivos.end(); ++it){
        archivoIterador =  *it;
        obtenerIndices = archivoIterador.getIndices();
        for(auto ind = obtenerIndices.begin(); ind != obtenerIndices.end(); ++ind){
            strcpy(indiceStruct.NombreArchivo, archivoIterador.getName().c_str());
            //palabra
            strcpy(indiceStruct.palabra, (*ind).first.c_str());
            //cantidad de veces encontrada
            indiceStruct.cantOcu = (*ind).second;
            archivoBinario.write((char*)&indiceStruct, sizeof(indiceStruct));
        }
    }
    archivoBinario.close();
}

std::vector<structInd> GestorArchivoBinario::leerArchivo(string directorio, string ocurrencia)
{
    std::ifstream file(directorio +"\\Indice.dat", std::ios::binary | std::ios::in );
    structInd indiceStruct;
    std::vector<structInd> indices;

    while(file.read((char*)&indiceStruct, sizeof (indiceStruct)))
    {
        if(!ocurrencia.empty()){
            if(strcmp(indiceStruct.palabra,ocurrencia.c_str()) == 0)
                indices.push_back(indiceStruct);
         }else{
             indices.push_back(indiceStruct);
         }
    }

    return indices;
}

std::vector<structInd> GestorArchivoBinario::leerTodoElContenidoDelArchivo(std::string directorio)
{
    return leerArchivo(directorio);
}

std::vector<structInd> GestorArchivoBinario::leerArchivoPorOcurrencia(string directorio, string ocurrencia)
{
    return leerArchivo(directorio,ocurrencia);
}

#include "ocurrencia.h"
#include <iostream>
#include "string.h"
#include "fstream"

Ocurrencia::Ocurrencia()
{
    this->totalOcurrencias = 0;
    this->rutaArchivoBinario = nullptr;
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

                //agrega linea linea y posicion al binario
                this->add_aBinario(i-tamanioOcu+1, linea, file);

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
    this->setTotalOcurrencias(cuentaOcurrencia);
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
    this->totalOcurrencias += total;
}

int Ocurrencia::getCantOcurrencias()
{
    return totalOcurrencias;
}

void Ocurrencia::setRutaArchivoBinario(char *path)
{
    if(rutaArchivoBinario == nullptr){
        this->rutaArchivoBinario = new char[strlen(path)+17];
        strcpy(rutaArchivoBinario,path);
        strcat(rutaArchivoBinario, "\\ocurrencias.dat");
    }
}

std::vector<ocurrenciaStruct> Ocurrencia::getLinea_yPos(char* nombreArchivo)
{
    std::ifstream file(rutaArchivoBinario, std::ios::binary | std::ios::in );
     ocurrenciaStruct ocuStruct;
    std::vector<ocurrenciaStruct> vectorOcs;

    while(!file.eof()){

        file.read((char*)&ocuStruct, sizeof (ocuStruct));
        if(!file.eof()){
                if(strcmp(ocuStruct.nombreArch , nombreArchivo)==0 && strcmp(ocuStruct.ocurrencia, ocurrencia)==0){
                vectorOcs.push_back(ocuStruct);
            }
        }
       }
    file.close();
    return vectorOcs;
}


void Ocurrencia::add_aBinario(int posOcurrencia, int linea, char* file)
{
    std::ofstream archivo;
    ocurrenciaStruct ocuStruct;
    archivo.open(rutaArchivoBinario,std::ios::binary | std::ios::out | std::ios::app);

    ocuStruct.pos = posOcurrencia;
    ocuStruct.linea = linea;
    strcpy(ocuStruct.ocurrencia, this->ocurrencia);
    strcpy(ocuStruct.nombreArch, file);
    archivo.write((char*)&ocuStruct, sizeof (ocuStruct));

    archivo.close();
}

void Ocurrencia::actualizarBinarioOcurrencias()
{
    std::ifstream file(rutaArchivoBinario, std::ios::binary | std::ios::in );
     ocurrenciaStruct ocuStruct;
    std::vector<ocurrenciaStruct> vectorOcs;

    while(!file.eof()){

        file.read((char*)&ocuStruct, sizeof (ocuStruct));
        if(!file.eof()){
             if(strcmp(ocuStruct.nombreArch , nombreArchivo)!=0)
             {
                vectorOcs.push_back(ocuStruct);       
             }
        }
       }
    file.close();
    std::vector<ocurrenciaStruct> ocusActualizadas = getLinea_yPos(nombreArchivo);

    std::ofstream archivoEntrada;
    archivoEntrada.open(rutaArchivoBinario,std::ios::binary | std::ios::out);

    for(std::vector<ocurrenciaStruct>::iterator it = vectorOcs.begin(); it != vectorOcs.end(); ++it){
         ocuStruct = *it;

         archivoEntrada.write((char*)&ocuStruct, sizeof (ocuStruct));
    }
    for(std::vector<ocurrenciaStruct>::iterator it = ocusActualizadas.begin(); it != ocusActualizadas.end(); ++it){
        ocuStruct = *it;
         archivoEntrada.write((char*)&ocuStruct, sizeof (ocuStruct));
    }
    archivoEntrada.close();


}

void Ocurrencia::setNombreArchivo(char *nombre)
{
    this->nombreArchivo = nombre;
}

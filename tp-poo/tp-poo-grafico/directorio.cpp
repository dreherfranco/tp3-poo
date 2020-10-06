#include "directorio.h"
#include "fstream"
#include <string.h>
#include <stdio.h>

using namespace std;

Directorio::Directorio()
{
    this->archivos = nullptr;
}

void Directorio::setListaArchivos(const char* pathDir)
{
    DIR * directorio;
    //struct que contiene al archivo o carpeta con su nombre y demas caracteristicas
    struct dirent * elemento;
    char* elem;
    char* extension = "txt";

    //Comprueba si es posible abrir el directorio
    if (directorio = opendir(pathDir))
    {

         //Lee cada uno de los elementos del directorio, carpetas y archivos
         while (elemento = readdir(directorio))
         {
              //elemento->d_name es el nombre de la carpeta o el archivo
              elem = elemento->d_name;

              //comprueba si la extension es .txt
              if(this->isTXT(elem,extension)){

                  int tamanio = elemento->d_namlen;
                  char* file = nullptr;
                  //Asigno memoria a la variable llamada file de tipo char*
                  file = new char[tamanio+1];
                  //Inserto en file el nombre del archivo que va a ser de tipo txt
                  file = strcpy(file, elemento->d_name);

                  //Agrega archivo a this->archivos
                  addArchivo(file);
              }

          }

    }
    closedir(directorio);
  }


char **Directorio::getArchivos()
{
    return archivos;
}

void Directorio::addArchivo(char *file)
{
    //Auxiliar para agregar los nombres de los archivos
    char** aux = new char*[this->cantArchivos+1];

    for(int i=0; i<this->cantArchivos; i++){
        aux[i] = this->archivos[i];
    }

    aux[this->cantArchivos] = file;
    delete[] this->archivos;
    this->archivos = aux;

    this->cantArchivos++;
}


bool Directorio::isTXT(char *nombreArchivo, char* extension)
{
    int cuentaOcurrencia = 0;
    int j = 0;
    int i=0;
    while(nombreArchivo[i] != '\0'){

        while(extension[j] == nombreArchivo[i]){
            // Se le restan 2 por el caracter nulo y por la longitud del arreglo, ya que este empieza a contar en 0
            if(j==1){
                //Cuenta la ocurrencia una vez que la cantidad del vector sea igual al valor que haya acumulado j
                cuentaOcurrencia++;
            }
            j++;
            //la variable i tendra que ir a la par de j para comparar en la siguiente iteracion
            i++;
        }

        //se reinicia a 0 para volver a comprobar si hay ocurrencias una vez que termine la estructura while
        j=0;
        //contador del primer while
        i++;
    }

    if(cuentaOcurrencia >= 1)
        return true;
    else
        return false;

}

int Directorio::getCantArchivos()
{
    return cantArchivos;

}



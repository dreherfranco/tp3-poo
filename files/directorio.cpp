#include "directorio.h"
#include "fstream"
#include <string.h>
#include <stdio.h>

Directorio::Directorio(std::string directorio)
{
    this->setDirectorio(directorio);
}

void Directorio::setDirectorio(std::string pathDir)
{
    DIR * directorio;
    //struct que contiene al archivo o carpeta con su nombre y demas caracteristicas
    struct dirent * elemento;
    char* elem;
    char* extension = ".txt";

    //Comprueba si es posible abrir el directorio
    if (directorio = opendir(pathDir.c_str()))
    {

         //Lee cada uno de los elementos del directorio, carpetas y archivos
         while (elemento = readdir(directorio))
         {
              //comprueba si la extension es .txt
              if(this->isTXT(elemento->d_name,extension)){

                  int tamanio = elemento->d_namlen;
                  char* file = nullptr;
                  file = new char[tamanio+1];
                  file = strcpy(file, elemento->d_name);

                  //Agrega archivo a this->archivos
                  addArchivo(file);
              }

          }

    }
    closedir(directorio);
  }


QStringList Directorio::getArchivos()
{
    return archivos;
}

void Directorio::addArchivo(QString file)
{
    this->archivos.push_back(file);
}


bool Directorio::isTXT(std::string nombreArchivo, std::string extension)
{
   int found = nombreArchivo.find(extension);
   if (found != -1)
       return true;
   else
       return false;
}

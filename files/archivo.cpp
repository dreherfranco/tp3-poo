#include "archivo.h"

#include <iostream>
#include <fstream>
#include "string.h"
#include <string>


Archivo::Archivo()
{

}

void Archivo :: setFileTxt(std::string fileName){
    std::ifstream file;
    file.open (fileName);
    std::string line;
    fileTxt = "";
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
              fileTxt = fileTxt + line + '\n';
        }
    }
    file.close();
}

std::string Archivo :: getFileTxt (){
    return fileTxt;
}

void Archivo::setName(string name)
{
    this->name = name;
}

string Archivo::getName()
{
    return name;
}

void Archivo::setIndices(string addressFile,std::string addressFilePreposiciones)
{
    indices = this->ocurrencia.setIndices(addressFile,addressFilePreposiciones);
}

std::map<std::string,int> Archivo::getIndices()
{
    return indices;
}

#ifndef ARCHIVO_H
#define ARCHIVO_H
#include "string"
#include "ocurrencia.h"

class Archivo
{
private:
    std::string fileTxt;
    Ocurrencia ocurrencia;
    std::string name;
    std::map<std::string,int> indices;
public:
    Archivo();
    void setFileTxt(std::string fileName);
    std::string getFileTxt();
    void setName(std::string name);
    std::string getName();
    std::map<std::string,int> getIndices();
    void setIndices(std::string addressFile,std::string addressFilePreposiciones);
};

#endif // ARCHIVO_H

#ifndef OCURRENCIA_H
#define OCURRENCIA_H
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <QDir>
#include "map"
using namespace std;

class Ocurrencia
{
private:
public:
    int getCantOcu(std::string addressFile, std::string wordFind);
    std::string deletePrep(QByteArray, std::string);
    std::map<std::string,int> setIndices(std::string addressFile,std::string addressFilePreposiciones);
    QByteArray insertarEspaciosEnPalabra(QByteArray palabra);
    Ocurrencia();
};

#endif // OCURRENCIA_H

#include "ocurrencia.h"
#include "string.h"
using namespace std;
Ocurrencia::Ocurrencia()
{

}

int Ocurrencia::getCantOcu(std::string addressFile, std::string wordFind){
   std::fstream file;
   file.open(addressFile, std::ios::in);
   int cantFound=0, posFinal=0, posInicial=0, tamanio = 0;
   std::string palabra, contenidoArchivo, buffer;
   QByteArray auxContenidoArchivo;

   while(getline(file,buffer)){
       contenidoArchivo += buffer + " ";
   }
   file.close();

   auxContenidoArchivo.push_back(contenidoArchivo.c_str());

   tamanio = contenidoArchivo.size();
       while(posInicial < tamanio){
           posFinal = contenidoArchivo.find(" ",posInicial);
           if(posFinal != -1){
              palabra = contenidoArchivo.substr(posInicial, posFinal-posInicial);
              posInicial = posFinal+1;
              if(palabra == wordFind){
                ++cantFound;
              }
           }else{
              palabra = contenidoArchivo.substr(posInicial, contenidoArchivo.size()-1);
              if(palabra == wordFind){
                ++cantFound;
              }
              posInicial = tamanio;
           }
       }
   return cantFound;
}

std::string Ocurrencia::deletePrep(QByteArray wordFind, string addressPrepDel){
    std::fstream file;
    std::string preposicion;
    QByteArray auxPrepo;
    int found = 0,cantFound=0;
    file.open(addressPrepDel, std::ios::in);
    if(file.is_open()){
            while(std::getline(file,preposicion))
            {              
                    auxPrepo = preposicion.c_str();
                    auxPrepo.trimmed();
                    auxPrepo = insertarEspaciosEnPalabra(auxPrepo);
                    wordFind = insertarEspaciosEnPalabra(wordFind);

                    found = wordFind.toStdString().find(auxPrepo.toStdString());
                    while(found != -1){
                        cantFound++;
                        found = wordFind.toStdString().find(auxPrepo.toStdString(), found + 1);
                    }
                    for(int i=0;i<cantFound;i++){
                        wordFind = insertarEspaciosEnPalabra(wordFind);
                        wordFind.replace(auxPrepo, " ");
                    }
            }
        wordFind = wordFind.trimmed();
    }
        file.close();

    return wordFind.toStdString();
}

std::map<string, int> Ocurrencia::setIndices(string addressFile, string addressFilePreposiciones)
{
    std::fstream file;
    file.open(addressFile, std::ios::in);
    std::string buffer, palabra;
    int posFinal=0, posInicial=0, tamanio;

    std::map<std::string,int> indices;
    std::string contenidoArchivo;
    QByteArray auxContenidoArchivo;

    while(getline(file,buffer)){
        contenidoArchivo += buffer + " ";
    }
    file.close();

    auxContenidoArchivo.push_back(contenidoArchivo.c_str());
    //borra preposiciones
    contenidoArchivo = deletePrep(auxContenidoArchivo,addressFilePreposiciones);

    tamanio = contenidoArchivo.size();
        while(posInicial < tamanio){
            posFinal = contenidoArchivo.find(" ",posInicial);
            if(posFinal != -1){
               palabra = contenidoArchivo.substr(posInicial, posFinal-posInicial);
               posInicial = posFinal+1;
               ++indices[palabra];
            }else{
               palabra = contenidoArchivo.substr(posInicial, contenidoArchivo.size()-1);
               ++indices[palabra];
               posInicial = tamanio;
            }
        }



        return indices;
}

QByteArray Ocurrencia::insertarEspaciosEnPalabra(QByteArray palabra)
{
    palabra.append(" ");
    palabra.prepend(" ");
    return palabra;
}

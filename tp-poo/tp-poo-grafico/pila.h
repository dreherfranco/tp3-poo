#ifndef PILA_H
#define PILA_H
struct NodoP{
    int posicionOcu;
    int linea;
    NodoP* sig;
};

class Pila
{
private:
    NodoP* pila;
    int cantNodos=0;
public:
    Pila();
    void add(int posOcurrencia, int linea);
    int* getLinea_y_Pos();
    int getCantNodos();
    void setCantNodos(int cantNodos);
};

#endif // PILA_H

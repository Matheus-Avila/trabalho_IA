#ifndef Algoritmo_h
#define Algoritmo_h
#include "Node.h"

class Algoritmo{
    private:
        Node* raiz;
        Node* atual;
        Node* lista_abertos;
        Node* lista_fechados;
        Node* pilha_abertos;//MUDAR PARA A ESTRUTURA PRONTA DO C++
        //incluir estatisticas
    public:
        Algoritmo(/* args */);
        ~Algoritmo();
};

Algoritmo::Algoritmo(/* args */)
{
}

Algoritmo::~Algoritmo()
{
}

#endif
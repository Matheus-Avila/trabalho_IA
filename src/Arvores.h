#ifndef Arvores_h
#define Arvores_h
#include "src/Node.h"

class Arvores{
    private:
        Node* raiz;
        Node* atual;
        Node* lista_abertos;
        Node* lista_fechados;
        Node* pilha_abertos;//MUDAR PARA A ESTRUTURA PRONTA DO C++
    public:
        Arvores(/* args */);
        ~Arvores();
};

Arvores::Arvores(/* args */)
{
}

Arvores::~Arvores()
{
}


#endif
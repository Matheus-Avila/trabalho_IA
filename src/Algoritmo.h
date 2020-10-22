#ifndef Algoritmo_h
#define Algoritmo_h
#include "Node.h"

class Algoritmo{
    private:
    public:
        Algoritmo(/* args */);
        bool checaVetor(vector<Node *> explorados, int x, int y);
        bool checaSolucao(Labirinto lab, Node* x);
        void printaSolucao(Node* x);
        ~Algoritmo();
};

Algoritmo::Algoritmo(/* args */)
{
}

Algoritmo::~Algoritmo()
{
}

 //printa os passos da solucao caso exista uma
void Algoritmo::printaSolucao(Node* x){
    
    if(x != NULL){
        Node *aux = x;
        string moves;

        while (aux != NULL)
        {
            moves.insert(0, 1, aux->get_acao());
            aux = aux->getPai();
        }
        cout << moves << endl;
    }else{
        cout << "Nao tem solucao" << endl;
    }
}

//checa se um no e solucao
bool Algoritmo::checaSolucao(Labirinto lab, Node* x){
    return (x->get_coordx() == lab.get_saida().x && x->get_coordy() == lab.get_saida().y);
}

//funcao que retorna true se algum elemento do vetor contem as coordenadas x e y, false c.c
bool Algoritmo::checaVetor(vector<Node *> explorados, int x, int y)
{

    for (int i = 0; i < explorados.size(); i++)
    {
        if (explorados[i]->get_coordx() == x && explorados[i]->get_coordy() == y)
        {
            return false;
        }
    }
    return true;
}
#endif
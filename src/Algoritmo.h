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
        void insertPriority(vector<Node *> &vet, Node *x);
        void replaceFrontier(vector<Node *> &vet, Node *x);
        int heuristica(int x, int y, Labirinto lab);
        ~Algoritmo();
};

Algoritmo::Algoritmo(/* args */)
{
}

Algoritmo::~Algoritmo()
{
}

//funcao heuristica que retorna o custo do no
int Algoritmo::heuristica(int x, int y, Labirinto lab){
    
    return (x - lab.get_saida().x + y - lab.get_saida().y);
}

//substitui um no x com menor custo no vetor vet
void Algoritmo::replaceFrontier(vector<Node *> &vet, Node *x)
{
    for (int i = 0; i < vet.size(); i++)
    {
        if (vet[i]->get_coordx() == x->get_coordx() && vet[i]->get_coordy() == x->get_coordy())
        {
            if (vet[i]->getCusto() > x->getCusto())
            {
                vet.erase(vet.begin() + i);
                insertPriority(vet, x);
            }
            return;
        }
    }
}

void Algoritmo::insertPriority(vector<Node *> &vet, Node *x)
{
    for (int i = 0; i < vet.size(); i++)
    {
        if (x->getCusto() < vet[i]->getCusto())
        {
            vet.insert(vet.begin() + i, x);
            return;
        }
    }
    vet.push_back(x);
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

//funcao que retorna false se algum elemento do vetor contem as coordenadas x e y, true c.c
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
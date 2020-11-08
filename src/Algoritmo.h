#ifndef Algoritmo_h
#define Algoritmo_h
#include "Node.h"
#include <time.h>

class Algoritmo{
    public:
        string estatisticas;
        clock_t inicio;
        clock_t fim;
        int fat_ramificacao;
        Algoritmo(/* args */);
        bool checaVetor(vector<Node *> explorados, int x, int y);
        bool checaSolucao(Labirinto lab, Node* x);
        void printaSolucao(Node* x);
        void insertPriority(vector<Node *> &vet, Node *x);
        void replaceFrontier(vector<Node *> &vet, Node *x);
        int heuristica(int x, int y, Labirinto lab);
        string getEstatisticas();
        ~Algoritmo();
};

Algoritmo::Algoritmo(/* args */)
{
}

Algoritmo::~Algoritmo()
{
    fat_ramificacao = 0;
}

string Algoritmo::getEstatisticas(){
    return this->estatisticas;
}

//funcao heuristica que retorna o custo do no
int Algoritmo::heuristica(int x, int y, Labirinto lab){
    
    return (abs(x - lab.get_saida().x) + abs(y - lab.get_saida().y));
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
        this->estatisticas += "Caminho:\n";
        this->estatisticas += moves;
        this->estatisticas += '\n';

        this->estatisticas += "Custo da solucao: ";
        this->estatisticas += to_string((moves.size() - 1));
        this->estatisticas += '\n';

        this->estatisticas += "Profundidade: ";
        this->estatisticas += to_string((moves.size() - 1));
        this->estatisticas += '\n';
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
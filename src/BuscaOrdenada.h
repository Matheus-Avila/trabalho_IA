#ifndef BuscaOrdenada_h
#define BuscaOrdenada_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"
#include <exception>
#include <queue>

class BuscaOrdenada : Algoritmo
{

private:
    Node *busca(Labirinto lab);
    void insertPriority(vector<Node *> vet, Node *x);
    void replaceFrontier(vector<Node *> vet, Node *x);

public:
    BuscaOrdenada(/* args */);
    ~BuscaOrdenada();
    void buscaOrdenada(Labirinto lab);
};

void BuscaOrdenada::insertPriority(vector<Node *> vet, Node *x)
{
    int i;
    for (i = 0; i < vet.size(); i++)
    {
        if (x->getCusto() < vet[i]->getCusto())
        {
            vet.insert(vet.begin() + i, x);
            break;
        }
    }
    vet.push_back(x);
}

//substitui um no x com menor custo no vetor vet
void BuscaOrdenada::replaceFrontier(vector<Node *> vet, Node *x)
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
            break;
        }
    }
}

BuscaOrdenada::BuscaOrdenada(/* args */)
{
}

BuscaOrdenada::~BuscaOrdenada()
{
}

void BuscaOrdenada::buscaOrdenada(Labirinto lab)
{
    Node *solution = busca(lab);
    printaSolucao(solution);
}

Node *BuscaOrdenada::busca(Labirinto lab)
{
    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);
    raiz->setCusto(0);

    vector<Node *> fronteira;
    vector<Node *> explorados;

    fronteira.push_back(raiz);

    //checa se raiz e solucao do problema
    if (checaSolucao(lab, raiz))
    {
        return raiz;
    }
    else
    {
        //Roda ate fronteira ficar vazia ou encontrar solucao
        while (true)
        {
            //nao a mais elementos para serem gerados
            if (fronteira.empty())
                return NULL;
            else
            {
                Node *atual = fronteira[0];
                fronteira.erase(fronteira.begin());

                if (checaSolucao(lab, atual))
                    return atual;

                explorados.push_back(atual);

                int x = atual->get_coordx();
                int y = atual->get_coordy();

                //checa se é possivel mover para cima, baixo, direita ou esquerda, nesta ordem, e
                //se a posicao ainda não foi explorada
                if (lab.podeMoverCima(x, y))
                {
                    Node *noFilho = new Node('C', x - 1, y, atual);
                    noFilho->setCusto(atual->getCusto() + 1);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x - 1, y))
                    {
                        if (checaVetor(fronteira, x - 1, y))
                        {
                            insertPriority(fronteira, noFilho);
                        }
                        else
                        {
                            //replace no com menor custo
                            replaceFrontier(fronteira, noFilho);
                        }
                    }
                }
                if (lab.podeMoverBaixo(x, y))
                {
                    Node *noFilho = new Node('B', x + 1, y, atual);
                    noFilho->setCusto(atual->getCusto() + 1);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x + 1, y))
                    {
                        if (checaVetor(fronteira, x + 1, y))
                        {
                            insertPriority(fronteira, noFilho);
                        }
                        else
                        {
                            //replace no com menor custo
                            replaceFrontier(fronteira, noFilho);
                        }
                    }
                }
                if (lab.podeMoverDireita(x, y))
                {
                    Node *noFilho = new Node('D', x, y + 1, atual);
                    noFilho->setCusto(atual->getCusto() + 1);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x, y + 1))
                    {
                        if (checaVetor(fronteira, x, y + 1))
                        {
                            insertPriority(fronteira, noFilho);
                        }
                        else
                        {
                            //replace no com menor custo
                            replaceFrontier(fronteira, noFilho);
                        }
                    }
                }
                if (lab.podeMoverEsquerda(x, y))
                {
                    Node *noFilho = new Node('E', x, y - 1, atual);
                    noFilho->setCusto(atual->getCusto() + 1);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x, y - 1))
                    {
                        if (checaVetor(fronteira, x, y - 1))
                        {
                            insertPriority(fronteira, noFilho);
                        }
                        else
                        {
                            //replace no com menor custo
                            replaceFrontier(fronteira, noFilho);
                        }
                    }
                }
            }
        }
    }
}
#endif
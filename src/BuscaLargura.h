#ifndef BuscaLargura_h
#define BuscaLargura_h

#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"

class BuscaLargura : Algoritmo
{
private:
    Node *busca_iterativa(Labirinto lab);

public:
    BuscaLargura(/* args */);
    ~BuscaLargura();
    void busca_largura(Labirinto lab);
};

BuscaLargura::BuscaLargura(/* args */)
{
}

BuscaLargura::~BuscaLargura()
{
}

void BuscaLargura::busca_largura(Labirinto lab)
{
    Node *solution = busca_iterativa(lab);
    printaSolucao(solution);
}

Node *BuscaLargura::busca_iterativa(Labirinto lab)
{
    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);

    vector<Node *> explorados;
    vector<Node *> fronteira;

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
                explorados.push_back(atual);

                int x = atual->get_coordx();
                int y = atual->get_coordy();

                //checa se é possivel mover para cima, baixo, direita ou esquerda, nesta ordem, e
                //se a posicao ainda não foi explorada
                if (lab.podeMoverCima(x, y))
                {
                    Node *noFilho = new Node('C', x - 1, y, atual);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x - 1, y) && checaVetor(fronteira, x - 1, y))
                    {
                        if (checaSolucao(lab, noFilho))
                        {
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
                if (lab.podeMoverBaixo(x, y))
                {
                    Node *noFilho = new Node('B', x + 1, y, atual);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x + 1, y) && checaVetor(fronteira, x + 1, y))
                    {
                        if (checaSolucao(lab, noFilho))
                        {
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
                if (lab.podeMoverDireita(x, y))
                {
                    Node *noFilho = new Node('D', x, y + 1, atual);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x, y + 1) && checaVetor(fronteira, x, y + 1))
                    {
                        if (checaSolucao(lab, noFilho))
                        {
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
                if (lab.podeMoverEsquerda(x, y))
                {
                    Node *noFilho = new Node('E', x, y - 1, atual);

                    //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                    if (checaVetor(explorados, x, y - 1) && checaVetor(fronteira, x, y - 1))
                    {
                        if (checaSolucao(lab, noFilho))
                        {
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
            }
        }
    }
}
#endif
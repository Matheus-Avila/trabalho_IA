#ifndef BuscaAEstrela_h
#define BuscaAEstrela_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"
#include <exception>
#include <queue>

class BuscaAEstrela : Algoritmo
{

private:
    Node *busca(Labirinto lab);

public:
    BuscaAEstrela(/* args */);
    ~BuscaAEstrela();
    void buscaAEstrela(Labirinto lab);
};

BuscaAEstrela::BuscaAEstrela(/* args */)
{
}

BuscaAEstrela::~BuscaAEstrela()
{
}

void BuscaAEstrela::buscaAEstrela(Labirinto lab)
{
    Node *solution = busca(lab);
    printaSolucao(solution);
}

Node *BuscaAEstrela::busca(Labirinto lab)
{
    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);
    raiz->setCusto(0 + heuristica(raiz->get_coordx(), raiz->get_coordy(), lab));

    vector<Node *> fronteira;
    vector<Node *> explorados;

    fronteira.push_back(raiz);

    //Roda ate fronteira ficar vazia ou encontrar solucao
    while (true)
    {
        //nao a mais elementos para serem gerados
        if (fronteira.empty()){
            return NULL;
        }
        else
        {
            Node *atual = fronteira[0];
            fronteira.erase(fronteira.begin());
            int custoheuristica = heuristica(atual->get_coordx(), atual->get_coordy(), lab);
            int custoGnPai = atual->getCusto() - custoheuristica;

            if (checaSolucao(lab, atual)){
                return atual;
            }
              
            explorados.push_back(atual);

            int x = atual->get_coordx();
            int y = atual->get_coordy();

            //checa se é possivel mover para cima, baixo, direita ou esquerda, nesta ordem, e
            //se a posicao ainda não foi explorada
            if (lab.podeMoverCima(x, y))
            {
                Node *noFilho = new Node('C', x - 1, y, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x - 1, y) && checaVetor(fronteira, x - 1, y))
                {
                    insertPriority(fronteira, noFilho);
                }
                else
                {
                    if (!checaVetor(fronteira, x - 1, y))
                    {
                        replaceFrontier(fronteira, noFilho);
                    }
                }
            }
            if (lab.podeMoverBaixo(x, y))
            {
                Node *noFilho = new Node('B', x + 1, y, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x + 1, y) && checaVetor(fronteira, x + 1, y))
                {
                    insertPriority(fronteira, noFilho);
                }
                else
                {
                    if (!checaVetor(fronteira, x + 1, y))
                    {
                        replaceFrontier(fronteira, noFilho);
                    }
                }
            }
            if (lab.podeMoverDireita(x, y))
            {
                Node *noFilho = new Node('D', x, y + 1, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x, y + 1) && checaVetor(fronteira, x, y + 1))
                {
                    insertPriority(fronteira, noFilho);
                }
                else
                {
                    if (!checaVetor(fronteira, x, y + 1))
                    {
                        replaceFrontier(fronteira, noFilho);
                    }
                }
            }
            if (lab.podeMoverEsquerda(x, y))
            {
                Node *noFilho = new Node('E', x, y - 1, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x, y - 1) && checaVetor(fronteira, x, y - 1))
                {
                    insertPriority(fronteira, noFilho);
                }
                else
                {
                    if (!checaVetor(fronteira, x, y - 1))
                    {
                        replaceFrontier(fronteira, noFilho);
                    }
                }
            }
        }
    }
}
#endif
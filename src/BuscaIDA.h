#ifndef BuscaIDA_h
#define BuscaIDA_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"

class BuscaIDA : Algoritmo
{
private:
    Node *busca(Labirinto lab);
    Node *iterativeA(Labirinto lab, vector<Node *> &explorados, vector<Node *> &fronteira, vector<Node *> &descartados, int patamar);

public:
    BuscaIDA(/* args */);
    ~BuscaIDA();
    void buscaIDA(Labirinto lab);
};

BuscaIDA::BuscaIDA(/* args */)
{
}

BuscaIDA::~BuscaIDA()
{
}

void BuscaIDA::buscaIDA(Labirinto lab)
{
    Node *solution = busca(lab);
    printaSolucao(solution);
}

Node *BuscaIDA::iterativeA(Labirinto lab, vector<Node *> &explorados, vector<Node *> &fronteira, vector<Node *> &descartados, int patamar)
{

    while (true)
    {
        if (fronteira.empty())
        {
            if (descartados.empty())
            {
                return NULL;
            }
            else
            {
                throw 3;
            }
        }
        else
        {
            Node *atual = fronteira[0];
            fronteira.erase(fronteira.begin());

            int custoheuristica = heuristica(atual->get_coordx(), atual->get_coordy(), lab);
            int custoGnPai = atual->getCusto() - custoheuristica;

            if (checaSolucao(lab, atual))
            {
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

                //checa se o custo do no eh menor que patamar
                if (noFilho->getCusto() <= patamar)
                {
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
                else
                {
                    insertPriority(descartados, noFilho);
                }
            }
            if (lab.podeMoverBaixo(x, y))
            {
                Node *noFilho = new Node('B', x + 1, y, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (noFilho->getCusto() <= patamar)
                {
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
                else
                {
                    insertPriority(descartados, noFilho);
                }
            }
            if (lab.podeMoverDireita(x, y))
            {
                Node *noFilho = new Node('D', x, y + 1, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (noFilho->getCusto() <= patamar)
                {
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
                else
                {
                    insertPriority(descartados, noFilho);
                }
            }
            if (lab.podeMoverEsquerda(x, y))
            {
                Node *noFilho = new Node('E', x, y - 1, atual);
                noFilho->setCusto(custoGnPai + 1 + heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (noFilho->getCusto() <= patamar)
                {
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
                else
                {
                    insertPriority(descartados, noFilho);
                }
            }
        }
    }
}

Node *BuscaIDA::busca(Labirinto lab)
{
    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);
    raiz->setCusto(0 + heuristica(raiz->get_coordx(), raiz->get_coordy(), lab));

    int patamar = raiz->getCusto();

    while (true)
    {
        vector<Node *> fronteira;
        vector<Node *> explorados;
        vector<Node *> descartados;

        fronteira.push_back(raiz);

        try
        {
            Node *solution = iterativeA(lab, explorados, fronteira, descartados, patamar);
            return solution;
        }
        catch (int e)
        {
            cout << "Patamar insuficiente: " << patamar << endl;
        }

        patamar = descartados[0]->getCusto();
        fronteira.clear();
        explorados.clear();
        descartados.clear();
    }
}
#endif
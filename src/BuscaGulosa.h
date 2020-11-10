#ifndef BuscaGulosa_h
#define BuscaGulosa_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"
#include <exception>
#include <queue>

class BuscaGulosa : public Algoritmo
{

private:
    Node *busca(Labirinto lab,  vector<Node *> &explorados);

public:
    BuscaGulosa(/* args */);
    ~BuscaGulosa();
    void buscaGulosa(Labirinto lab);
};

BuscaGulosa::BuscaGulosa(/* args */)
{
}

BuscaGulosa::~BuscaGulosa()
{
}

void BuscaGulosa::buscaGulosa(Labirinto lab)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector<Node *> explorados;
    Node *solution = busca(lab, explorados);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    this->estatisticas += "Busca Gulosa: \n";
    printaSolucao(solution);
    this->estatisticas += "Total de nos expandidos: " + to_string(explorados.size()) + '\n';
    this->estatisticas += "Total de nos visitados: " + to_string(this->fat_ramificacao) + '\n';
    this->estatisticas += "Fator de ramificacao medio: " + to_string(((float)this->fat_ramificacao/(float)explorados.size())) + '\n';
    this->estatisticas += "Tempo de execucao: " + to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) + " microsegundos" + '\n';
}

Node *BuscaGulosa::busca(Labirinto lab, vector<Node *> &explorados)
{
    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);
    raiz->setCusto(heuristica(raiz->get_coordx(), raiz->get_coordy(), lab));

    vector<Node *> fronteira;
    fronteira.push_back(raiz);

    //Roda ate fronteira ficar vazia ou encontrar solucao
    while (true)
    {
        //nao a mais elementos para serem gerados
        if (fronteira.empty())
        {
            return NULL;
        }
        else
        {
            Node *atual = fronteira[0];
            fronteira.erase(fronteira.begin());

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
                noFilho->setCusto(heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x - 1, y) && checaVetor(fronteira, x - 1, y))
                {
                    this->fat_ramificacao++;
                    insertPriority(fronteira, noFilho);
                }
            }
            if (lab.podeMoverBaixo(x, y))
            {
                Node *noFilho = new Node('B', x + 1, y, atual);
                noFilho->setCusto(heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x + 1, y) && checaVetor(fronteira, x + 1, y))
                {
                    this->fat_ramificacao++;
                    insertPriority(fronteira, noFilho);
                }
            }
            if (lab.podeMoverDireita(x, y))
            {
                Node *noFilho = new Node('D', x, y + 1, atual);
                noFilho->setCusto(heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x, y + 1) && checaVetor(fronteira, x, y + 1))
                {
                    this->fat_ramificacao++;
                    insertPriority(fronteira, noFilho);
                }
            }
            if (lab.podeMoverEsquerda(x, y))
            {
                Node *noFilho = new Node('E', x, y - 1, atual);
                noFilho->setCusto(heuristica(noFilho->get_coordx(), noFilho->get_coordy(), lab));

                //checa se a posicao nao esta nem no vetor de explorados e na fronteira
                if (checaVetor(explorados, x, y - 1) && checaVetor(fronteira, x, y - 1))
                {
                    this->fat_ramificacao++;
                    insertPriority(fronteira, noFilho);
                }
            }
        }
    }
}
#endif
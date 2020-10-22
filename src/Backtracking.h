#ifndef Backtracking_h
#define Backtracking_h

#include "Algoritmo.h"
#include "Node.h"
#include "Labirinto.h"
#include <vector>

class Backtracking : public Algoritmo
{
private:
    Node *recursive_Backtracking(Labirinto lab, vector<Node *> explorados, Node *estadoatual);

public:
    void backtracking(Labirinto lab);
};

void Backtracking::backtracking(Labirinto lab)
{
    coordenadas entrada = lab.get_entrada();
    Node *raiz = new Node('x', entrada.x, entrada.y, NULL);
    vector<Node *> explorados;

    Node *solution = recursive_Backtracking(lab, explorados, raiz);
    printaSolucao(solution);
}

Node *Backtracking::recursive_Backtracking(Labirinto lab, vector<Node *> explorados, Node *estadoAtual)
{
    explorados.push_back(estadoAtual);

    //verifica se estado atual e solucao do labirinto
    if (checaSolucao(lab, estadoAtual))
    {
        return estadoAtual;
    }
    else
    {
        int x = estadoAtual->get_coordx();
        int y = estadoAtual->get_coordy();

        //checa se é possivel mover para cima, baixo, direita ou esquerda, nesta ordem, e
        //se a posicao ainda não foi explorada

        if (lab.podeMoverCima(x, y) && checaVetor(explorados, x - 1, y))
        {
            Node *noFilho = new Node('C', x - 1, y, estadoAtual);
            Node *solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        if (lab.podeMoverBaixo(x, y) && checaVetor(explorados, x + 1, y))
        {
            Node *noFilho = new Node('B', x + 1, y, estadoAtual);
            Node *solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        if (lab.podeMoverDireita(x, y) && checaVetor(explorados, x, y + 1))
        {
            Node *noFilho = new Node('D', x, y + 1, estadoAtual);
            Node *solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        if (lab.podeMoverEsquerda(x, y) && checaVetor(explorados, x, y - 1))
        {
            Node *noFilho = new Node('E', x, y - 1, estadoAtual);
            Node *solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        //Não existe mais nó a ser explorado
        return NULL;
    }
}
#endif
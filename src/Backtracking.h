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
    bool checaExplorado(vector<Node *> explorados, int x, int y);

public:
    void backtracking(Labirinto lab);
};

bool Backtracking::checaExplorado(vector<Node *> explorados, int x, int y)
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

void Backtracking::backtracking(Labirinto lab)
{

    coordenadas entrada = lab.get_entrada();
    Node *raiz = new Node('x', entrada.x, entrada.y, NULL);

    vector<Node *> explorados;

    cout << "TESTE" << endl;
    Node *solution = recursive_Backtracking(lab, explorados, raiz);
    cout << "TESTE" << endl;
    cout << solution->get_coordx() + " " + solution->get_coordy() << endl;

    if(solution != NULL){
        Node* aux = solution;

        while(aux != NULL){
            cout << aux->get_acao() << " ";
            aux = aux->getPai();
        }
    }
    else{
        cout << "Nao tem solucao" << endl;
    }
}

Node *Backtracking::recursive_Backtracking(Labirinto lab, vector<Node *> explorados, Node *estadoAtual)
{

    explorados.push_back(estadoAtual);

    if (estadoAtual->get_coordx() == lab.get_saida().x && estadoAtual->get_coordy() == lab.get_saida().y)
    {
        return estadoAtual;
    }
    else
    {
        //checa se é possivel mover para cima, baixo, direita ou esquerda, nesta ordem,
        //se a posicao ainda não foi explorada

        int x = estadoAtual->get_coordx();
        int y = estadoAtual->get_coordy();

        if (lab.podeMoverCima(x, y) && checaExplorado(explorados, x - 1, y))
        {
            Node* noFilho = new Node('C', x - 1, y, estadoAtual);
            Node* solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        if (lab.podeMoverBaixo(x, y) && checaExplorado(explorados, x + 1, y))
        {
            Node* noFilho = new Node('B', x + 1, y, estadoAtual);
            Node* solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        if (lab.podeMoverDireita(x, y) && checaExplorado(explorados, x, y + 1))
        {
            Node* noFilho = new Node('D', x, y + 1, estadoAtual);
            Node* solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }
        if (lab.podeMoverEsquerda(x, y) && checaExplorado(explorados, x, y - 1))
        {
            Node* noFilho = new Node('E', x, y - 1, estadoAtual);
            Node* solution = recursive_Backtracking(lab, explorados, noFilho);

            if (solution != NULL)
                return solution;
        }

        //Não existe mais nó para ser explorado
        return nullptr;
    }
}

#endif
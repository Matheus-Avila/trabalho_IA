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
    bool checaExplorado(vector<Node *> explorados, int x, int y);
    bool checaFronteira(vector<Node *> fronteira, int x, int y);
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

bool BuscaLargura::checaFronteira(vector<Node *> fronteira, int x, int y)
{

    for (int i = 0; i < fronteira.size(); i++)
    {
        if (fronteira[i]->get_coordx() == x && fronteira[i]->get_coordy() == y)
        {
            return false;
        }
    }
    return true;
}

bool BuscaLargura::checaExplorado(vector<Node *> explorados, int x, int y)
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

void BuscaLargura::busca_largura(Labirinto lab)
{

    Node *solution = busca_iterativa(lab);
    
    if(solution != NULL){
        Node* aux = solution;
        string moves;

        while(aux != NULL){
            moves.insert(0,1, aux->get_acao());
            aux = aux->getPai();
        }
        cout << moves << endl;
    }
    else{
        cout << "Nao tem solucao" << endl;
    }

}

Node *BuscaLargura::busca_iterativa(Labirinto lab)
{

    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);

    vector<Node *> explorados;
    vector<Node *> fronteira;

    fronteira.push_back(raiz);
    if (raiz->get_coordx() == lab.get_saida().x && raiz->get_coordy() == lab.get_saida().y)
    {
        return raiz;
    }
    else
    {
        while (true)
        {
            if (fronteira.empty())
                return NULL;
            else
            {
                Node *atual = fronteira[0];
                fronteira.erase(fronteira.begin());
                explorados.push_back(atual);

                int x = atual->get_coordx();
                int y = atual->get_coordy();

                if (lab.podeMoverCima(x, y))
                {
                    Node *noFilho = new Node('C', x - 1, y, atual);
                    if (checaExplorado(explorados, x - 1, y) && checaFronteira(fronteira, x - 1, y))
                    {
                        if (noFilho->get_coordx() == lab.get_saida().x &&
                        noFilho->get_coordy() == lab.get_saida().y){
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
                if (lab.podeMoverBaixo(x, y))
                {
                    Node *noFilho = new Node('B', x + 1, y, atual);
                    if (checaExplorado(explorados, x + 1, y) && checaFronteira(fronteira, x + 1, y))
                    {
                        if (noFilho->get_coordx() == lab.get_saida().x &&
                        noFilho->get_coordy() == lab.get_saida().y){
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
                if (lab.podeMoverDireita(x, y))
                {
                    Node *noFilho = new Node('D', x, y + 1, atual);
                    if (checaExplorado(explorados, x, y + 1) && checaFronteira(fronteira, x, y + 1))
                    {
                        if (noFilho->get_coordx() == lab.get_saida().x &&
                        noFilho->get_coordy() == lab.get_saida().y){
                            return noFilho;
                        }
                        fronteira.push_back(noFilho);
                    }
                }
                if (lab.podeMoverEsquerda(x, y))
                {
                    Node *noFilho = new Node('E', x, y - 1, atual);
                    if (checaExplorado(explorados, x, y - 1) && checaFronteira(fronteira, x, y - 1))
                    {
                        if (noFilho->get_coordx() == lab.get_saida().x &&
                        noFilho->get_coordy() == lab.get_saida().y){
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
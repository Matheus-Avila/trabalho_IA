#ifndef BuscaProfundidade_h
#define BuscaProfundidade_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"
#include <exception>

class BuscaProfundidadeLimitada
{

private:
    Node *recursiveDLS(Labirinto lab, Node *atual, int limite) throw(int);

public:
    BuscaProfundidadeLimitada(/* args */);
    ~BuscaProfundidadeLimitada();
    void busca_profundidade_limitada(Labirinto lab, int limite);
};

BuscaProfundidadeLimitada::BuscaProfundidadeLimitada(/* args */)
{
}

BuscaProfundidadeLimitada::~BuscaProfundidadeLimitada()
{
}

void BuscaProfundidadeLimitada::busca_profundidade_limitada(Labirinto lab, int limite)
{
    try
    {
        Node *raiz = new Node('X', lab.get_entrada().x, lab.get_entrada().y, NULL);
        Node *solution = recursiveDLS(lab, raiz, limite);
        if (solution != NULL)
        {
            Node *aux = solution;
            string moves;

            while (aux != NULL)
            {
                moves.insert(0, 1, aux->get_acao());
                aux = aux->getPai();
            }
            cout << moves << endl;
        }
        else
        {
            cout << "Nao tem solucao" << endl;
        }
    }
    catch (int error)
    {
        cout << "Limite atingido para o valor " << limite << endl;
    }
    //print solucao
}

Node *BuscaProfundidadeLimitada::recursiveDLS(Labirinto lab, Node *atual, int limite) throw(int)
{

    if (atual->get_coordx() == lab.get_saida().x && atual->get_coordy() == lab.get_saida().y)
    {
        return atual;
    }
    else
    { 
        if (limite == 0)
        {
            throw 2;
        }
        else
        {
            bool limite_atingido = false;

            int x = atual->get_coordx();
            int y = atual->get_coordy();

            if (lab.podeMoverCima(x, y) && (atual->get_acao() != 'B'))
            {
                Node *noFilho = new Node('C', x - 1, y, atual);
                try
                { 
                    Node *resultado = recursiveDLS(lab, noFilho, limite - 1);
                    return resultado;
                }
                catch (int e)
                {
                    limite_atingido = true;
                }
            }

            if (lab.podeMoverBaixo(x, y) && (atual->get_acao() != 'C'))
            {
                Node *noFilho = new Node('B', x + 1, y, atual);
                try
                {
                    Node *resultado = recursiveDLS(lab, noFilho, limite - 1);
                    return resultado;
                }
                catch (int e)
                {
                    limite_atingido = true;
                }
            }

            if (lab.podeMoverDireita(x, y) && (atual->get_acao() != 'E'))
            {
                Node *noFilho = new Node('D', x, y + 1, atual);
                try
                {
                    Node *resultado = recursiveDLS(lab, noFilho, limite - 1);
                    return resultado;
                }
                catch (int e)
                {
                    limite_atingido = true;
                }
            }

            if (lab.podeMoverEsquerda(x, y)&& (atual->get_acao() != 'D'))
            {
                Node *noFilho = new Node('E', x, y - 1, atual);
                try
                {
                    Node *resultado = recursiveDLS(lab, noFilho, limite - 1);
                    return resultado;
                }
                catch (int e)
                {
                    limite_atingido = true;
                }
            }

            if (limite_atingido)
            {
                throw 2;
            }
            else
            {
                return NULL;
            }
        }
    }
}

#endif
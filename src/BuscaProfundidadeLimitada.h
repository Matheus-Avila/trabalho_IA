#ifndef BuscaProfundidade_h
#define BuscaProfundidade_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"
#include <exception>

class BuscaProfundidadeLimitada : Algoritmo
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
        Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);
        Node *solution = recursiveDLS(lab, raiz, limite);

        printaSolucao(solution);
    }
    catch (int error)
    {
        cout << "Limite atingido para o valor " << limite << endl;
    }
}

//funcao que retorna um no solucao ou dispara um valor 2 caso atindido o limite
Node *BuscaProfundidadeLimitada::recursiveDLS(Labirinto lab, Node *atual, int limite) throw(int)
{
    if (checaSolucao(lab, atual))
    {
        return atual;
    }
    else
    { 
        if (limite == 0)
        {
            //lanca excecao
            throw 2;
        }
        else
        {
            bool limite_atingido = false;

            int x = atual->get_coordx();
            int y = atual->get_coordy();
            
            //retorna uma solucao somente se o no e diferente de NULL, caso contrario continua procurando uma solucao
            if (lab.podeMoverCima(x, y) && (atual->get_acao() != 'B'))
            {
                Node *noFilho = new Node('C', x - 1, y, atual);
                try
                { 
                    Node *resultado = recursiveDLS(lab, noFilho, limite - 1);
                    if(resultado != NULL)
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
                    if(resultado != NULL)
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
                    if(resultado != NULL)
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
                    if(resultado != NULL)
                        return resultado;
                }
                catch (int e)
                {
                    limite_atingido = true;
                }
            }

            if (limite_atingido)
            {
                //o limite foi atingido para alguma das acoes possiveis para o no atual
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
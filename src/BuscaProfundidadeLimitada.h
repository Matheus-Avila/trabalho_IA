#ifndef BuscaProfundidade_h
#define BuscaProfundidade_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"

class BuscaProfundidadeLimitada : public  Algoritmo
{

private:
    Node *recursiveDLS(Labirinto lab, Node *atual, int limite);
    int qtdeplorados;

public:
    BuscaProfundidadeLimitada(/* args */);
    ~BuscaProfundidadeLimitada();
    void busca_profundidade_limitada(Labirinto lab, int limite);
};

BuscaProfundidadeLimitada::BuscaProfundidadeLimitada(/* args */)
{
    qtdeplorados = 0;
}

BuscaProfundidadeLimitada::~BuscaProfundidadeLimitada()
{
}

void BuscaProfundidadeLimitada::busca_profundidade_limitada(Labirinto lab, int limite)
{
    try
    {
    Node *raiz = new Node('x', lab.get_entrada().x, lab.get_entrada().y, NULL);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Node *solution = recursiveDLS(lab, raiz, limite);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    this->estatisticas += "Busca Profundidade limitada: \nLimite " + to_string(limite) + '\n';
    printaSolucao(solution);
    this->estatisticas += "Total de nos expandidos: " + to_string(qtdeplorados) + '\n';
    this->estatisticas += "Total de nos visitados: " + to_string(this->fat_ramificacao) + '\n';
    this->estatisticas += "Fator de ramificacao medio: " + to_string(((float)this->fat_ramificacao/(float)qtdeplorados)) + '\n';
    this->estatisticas += "Tempo de execucao: " + to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) + " microsegundos" + '\n';
    }
    catch (int error)
    {
        cout << "Limite atingido para o valor " << limite << endl;
    }
}

//funcao que retorna um no solucao ou dispara um valor 2 caso atindido o limite
Node *BuscaProfundidadeLimitada::recursiveDLS(Labirinto lab, Node *atual, int limite)
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
            
            qtdeplorados++;

            //retorna uma solucao somente se o no e diferente de NULL, caso contrario continua procurando uma solucao
            if (lab.podeMoverCima(x, y) && (atual->get_acao() != 'B'))
            {
                Node *noFilho = new Node('C', x - 1, y, atual);
                this->fat_ramificacao++;
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
                this->fat_ramificacao++;
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
                this->fat_ramificacao++;
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
                this->fat_ramificacao++;
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
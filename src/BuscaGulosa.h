#ifndef BuscaGulosa_h
#define BuscaGulosa_h
#include "Algoritmo.h"
#include <vector>
#include "Labirinto.h"
#include "Node.h"
#include <algorithm>

struct movimento
{
    char operacao;
    int custo;
};


class BuscaGulosa : Algoritmo
{
private:
    int verificaDistancia(int x, int y, Labirinto lab);
    Node* busca_gulosa_recursiva(Labirinto lab, Node* atual);
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

int BuscaGulosa::verificaDistancia(int x, int y, Labirinto lab){
    
    return x - lab.get_saida().x + y - lab.get_saida().y;
}

void BuscaGulosa::buscaGulosa(Labirinto lab){
    coordenadas entrada = lab.get_entrada();
    Node *raiz = new Node('x', entrada.x, entrada.y, NULL);
    vector<Node *> explorados;

    Node *solution = busca_gulosa_recursiva(lab, raiz);
    printaSolucao(solution);
}

Node* BuscaGulosa::busca_gulosa_recursiva(Labirinto lab, Node* atual){

    if (checaSolucao(lab, atual))
    {
        return atual;

    }else{
        vector<movimento> movimentos_possiveis;
        int x = atual->get_coordx();
        int y = atual->get_coordy();
        movimento aux_mov;
        int aux;

        //Pode mover para cima
        if(lab.podeMoverCima(x-1, y) && atual->get_acao() != 'B'){
            aux = verificaDistancia(x-1, y, lab);
            aux_mov.custo = 'C';
            aux_mov.operacao = aux;
            movimentos_possiveis.push_back(aux_mov); 
        }
        //Pode mover para baixo
        if(lab.podeMoverBaixo(x+1 , y) && atual->get_acao() != 'C'){
            aux = verificaDistancia(x+1, y, lab);
            aux_mov.custo = 'B';
            aux_mov.operacao = aux;
            movimentos_possiveis.push_back(aux_mov); 
        }
        //Pode mover para direita
        if(lab.podeMoverDireita(x, y+1) && atual->get_acao() != 'E'){
            aux = verificaDistancia(x, y+1, lab);
            aux_mov.custo = 'D';
            aux_mov.operacao = aux;
            movimentos_possiveis.push_back(aux_mov); 
        }
        //Pode mover para esquerda
        if(lab.podeMoverEsquerda(x, y-1) && atual->get_acao() != 'D'){
            aux = verificaDistancia(x, y-1, lab);
            aux_mov.custo = 'E';
            aux_mov.operacao = aux;
            movimentos_possiveis.push_back(aux_mov); 
        }
        //Ordenacao provavelmente errada!!!!!
        sort(movimentos_possiveis.begin(), movimentos_possiveis.end());
        while(!movimentos_possiveis.empty()){
        
            aux_mov = movimentos_possiveis[0];
            movimentos_possiveis.erase(movimentos_possiveis.begin());
            if(aux_mov.operacao == 'C'){
                Node* noFilho = new Node('C', x-1, y, atual);
                Node* solution = busca_gulosa_recursiva(lab, noFilho);
                if(solution != NULL){
                    return solution;
                }
            }
            if(aux_mov.operacao == 'B'){
                Node* noFilho = new Node('B', x+1, y, atual);
                Node* solution = busca_gulosa_recursiva(lab, noFilho);
                if(solution != NULL){
                    return solution;
                }
            }
            if(aux_mov.operacao == 'D'){
                Node* noFilho = new Node('D', x, y+1, atual);
                Node* solution = busca_gulosa_recursiva(lab, noFilho);
                if(solution != NULL){
                    return solution;
                }
            }
            if(aux_mov.operacao == 'E'){
                Node* noFilho = new Node('E', x, y-1, atual);
                Node* solution = busca_gulosa_recursiva(lab, noFilho);
                if(solution != NULL){
                    return solution;
                }
            }
        }
        return NULL;
    }
}

#endif
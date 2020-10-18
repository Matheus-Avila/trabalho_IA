#include "Labirinto.h"

#ifndef _Node_h_
#define _Node_h_

class Node
{
private:
    coordenadas coord;
    Node* pai;
    char acao;
    static int custo; //1
    int fat_ramificacao;
    Node** lista_filhos;// Quando nos chegarmos em um nó vamos precisar saber quais filhos ele tem
    //e qual a prioridade??
    int status;//aberto ou fechado. já foi expandido


public:
    Node(char acao, int x, int y, Node* pai);
    ~Node();
    void set_coords(int x, int y);
    int get_coordx();
    int get_coordy();
    void set_ramificacao(int ramificacao);
    int get_ramificacao();
    char get_acao();
    void expande_node();//Preencher a lista de filhos 

};

Node::Node(char acao, int x, int y, Node* pai){
    this->acao = acao;
    this->coord.x = x;
    this->coord.y = y;
    this->pai = pai;
}

Node::~Node(){

}

char Node::get_acao(){
    return acao;
}
int Node::get_coordx(){
    return this->coord.x;
}

int Node::get_coordy(){
    return this->coord.y;
}

void Node::set_coords(int x, int y){
    this->coord.x = x;
    this->coord.y = y;
}

void Node::set_ramificacao(int ramificacao){
    this->fat_ramificacao = ramificacao;
}

int Node::get_ramificacao(){
    return this->fat_ramificacao;
}
#endif
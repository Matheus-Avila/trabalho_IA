#include "Labirinto.h"

#ifndef _Node_h_
#define _Node_h_

class Node
{
private:
    coordenadas coord;
    Node* pai;
    char acao;
    int custo;

public:
    Node(char acao, int x, int y, Node* pai);
    ~Node();
    int get_coordx();
    int get_coordy();
    char get_acao();
    void setCusto(int custo);
    int getCusto();
    Node* getPai();
};

Node::Node(char acao, int x, int y, Node* pai){
    this->acao = acao;
    this->coord.x = x;
    this->coord.y = y;
    this->pai = pai;
}

Node::~Node(){

}

Node* Node::getPai(){
    return pai;
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

void Node::setCusto(int custo){
    this->custo = custo;
}

int Node::getCusto(){
    return custo;
}
#endif
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#ifndef _Labirinto_h_
#define _Labirinto_h_
struct coordenadas {
    int x;
    int y;
};

class Labirinto
{
private:
    bool** grid;
    coordenadas entrada;
    coordenadas saida;
    
public:
    Labirinto();
    void set_labirinto(string arquivo);
    coordenadas get_saida();
    coordenadas get_entrada();
    ~Labirinto();
};

Labirinto::Labirinto(){
}

Labirinto::~Labirinto(){
}

coordenadas Labirinto::get_entrada(){
    return entrada;
}

coordenadas Labirinto::get_saida(){
    return saida;
}

void Labirinto::set_labirinto(string arquivo){
    //fazer a leitura do arquivo e colocar no grid
    ifstream arq (arquivo);
    string line;
    if(arq.is_open()){
        getline(arq, line);
        cout << line << endl;
        string entrada_lab_x;
        string entrada_lab_y;
        entrada_lab_x = line.substr(0,line.find(" "));
        entrada_lab_y = line.substr(1,line.find(" "));
        
        cout << entrada_lab_x << endl;
        cout << entrada_lab_y << endl;
    }
    arq.close();
}
#endif
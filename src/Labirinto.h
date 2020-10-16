#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#ifndef _Labirinto_h_
#define _Labirinto_h_
struct coordenadas
{
    int x;
    int y;
};

class Labirinto
{
private:
    bool **grid;
    coordenadas entrada;
    coordenadas saida;
    void le_entrada(string labEntrada);
    void le_saida(string labSaida);

public:
    Labirinto();
    void set_labirinto(string arquivo);
    coordenadas get_saida();
    coordenadas get_entrada();
    ~Labirinto();
};

Labirinto::Labirinto()
{
}

Labirinto::~Labirinto()
{
}

coordenadas Labirinto::get_entrada()
{
    return entrada;
}

coordenadas Labirinto::get_saida()
{
    return saida;
}

void Labirinto::le_entrada(string labEntrada)
{
    int pos = labEntrada.find(' ');

    string token;
    token = labEntrada.substr(0, pos);

    this->entrada.x = stoi(token, nullptr, 10);
    labEntrada.erase(0, pos + 1);

    pos = labEntrada.find(' ');
    token = labEntrada.substr(0, pos);
    this->entrada.y = stoi(token, nullptr, 10);
}

void Labirinto::le_saida(string labSaida)
{
    int pos = labSaida.find(' ');

    string token;
    token = labSaida.substr(0, pos);

    this->saida.x = stoi(token, nullptr, 10);
    labSaida.erase(0, pos + 1);

    pos = labSaida.find(' ');
    token = labSaida.substr(0, pos);
    this->saida.y = stoi(token, nullptr, 10);

}

string removeEspacos (string str){
    std::string output;
    output.reserve(str.size()); // optional, avoids buffer reallocations in the loop
    for(size_t i = 0; i < str.size(); ++i)
        if(str[i] != ' ') output += str[i];

    return output;
}

void Labirinto::set_labirinto(string arquivo)
{
    //fazer a leitura do arquivo e colocar no grid
    ifstream arq(arquivo);
    string line;

    if (arq.is_open())
    {
        //le entrada do labirinto
        getline(arq, line);
        le_entrada(line);

        //le saida do labirinto
        getline(arq, line);
        le_saida(line);

        //guarda as linhas do labirinto
        vector<string> lines;
        while(getline(arq, line)){
            lines.push_back(line);
        }

        lines[0] = removeEspacos(lines[0]);

        int linhas = lines.size();
        int colunas = lines[0].size();

        grid = new bool[linhas][colunas];
    }
    arq.close();
}
#endif
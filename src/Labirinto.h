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
    int linhas;
    int colunas;
    coordenadas entrada;
    coordenadas saida;
    void le_entrada(string labEntrada);
    void le_saida(string labSaida);

public:
    Labirinto();
    void set_labirinto(string arquivo);
    coordenadas get_saida();
    coordenadas get_entrada();
    bool** get_grid();
    bool podeMoverCima(int x, int y);
    bool podeMoverBaixo(int x, int y);
    bool podeMoverDireita(int x, int y);
    bool podeMoverEsquerda(int x, int y);

    ~Labirinto();
};

Labirinto::Labirinto()
{
}

Labirinto::~Labirinto()
{
}

bool Labirinto::podeMoverCima(int x, int y){

    if(x > 0){
        return grid[x - 1][y];
    }
    return false;
}

bool Labirinto::podeMoverBaixo(int x, int y){

    if(x < linhas - 1){
        return grid[x + 1][y];
    }
    return false;
}

bool Labirinto::podeMoverDireita(int x, int y){

    if(y < colunas - 1){
        return grid[x][y + 1];
    }
    return false;
}

bool Labirinto::podeMoverEsquerda(int x, int y){

    if(y > 0){
        return grid[x][y - 1];
    }
    return false;
}

coordenadas Labirinto::get_entrada()
{
    return entrada;
}

coordenadas Labirinto::get_saida()
{
    return saida;
}

bool** Labirinto::get_grid(){
    return this->grid;
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

string removeEspacos(string str)
{
    std::string output;
    output.reserve(str.size());
    size_t i;
    for (size_t i = 0; i < str.size(); i++)
        if (str[i] != ' ')
        {
            output += str[i];
        }
    cout << "ultimo indice: " << output[i - 1] << endl;
    return output;
}

void Labirinto::set_labirinto(string arquivo)
{
    //faz a leitura do arquivo e coloca no grid
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
        while (getline(arq, line))
            lines.push_back(line);

        this->linhas = lines.size();
        this->colunas = lines[0].size() - 1;

        //inicializa o grid
        grid = new bool *[linhas];
        for (int i = 0; i < linhas; i++)
            grid[i] = new bool[colunas];

        //converte as entradas do arquivo para o grid de bools
        for (int i = 0; i < linhas; i++)
            for (int j = 0; j < colunas; j++)
                grid[i][j] = (lines[i][j] == '0') ? true : false;
    }
    arq.close();
}
#endif
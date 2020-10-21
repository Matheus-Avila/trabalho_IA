#include "src/Labirinto.h"
#include "src/Node.h"
#include "src/Algoritmo.h"
#include "src/Backtracking.h"
#include "src/BuscaLargura.h"
#include "src/BuscaProfundidadeLimitada.h"
#include <exception>

using namespace std;

int main()
{
    Labirinto *lab = new Labirinto();
    lab->set_labirinto("Labirintos/lab2.txt");

    Backtracking* bt = new Backtracking();
    bt->backtracking(*lab);

    BuscaLargura* bl = new BuscaLargura();
    bl->busca_largura(*lab);

    BuscaProfundidadeLimitada* bp = new BuscaProfundidadeLimitada();
    bp->busca_profundidade_limitada(*lab, 8);

    return 0;
}
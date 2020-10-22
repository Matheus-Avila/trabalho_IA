#include "src/Labirinto.h"
#include "src/Backtracking.h"
#include "src/BuscaLargura.h"
#include "src/BuscaProfundidadeLimitada.h"
#include "src/BuscaOrdenada.h"

using namespace std;

int main()
{
    Labirinto *lab = new Labirinto();
    lab->set_labirinto("Labirintos/lab1.txt");

    /*
    Backtracking* bt = new Backtracking();
    bt->backtracking(*lab);

    BuscaLargura* bl = new BuscaLargura();
    bl->busca_largura(*lab);

    BuscaProfundidadeLimitada* bp = new BuscaProfundidadeLimitada();
    bp->busca_profundidade_limitada(*lab, 50);
    */

    BuscaOrdenada* bl = new BuscaOrdenada();
    bl->buscaOrdenada(*lab);

    return 0;
}
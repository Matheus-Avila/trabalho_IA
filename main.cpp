#include "src/Labirinto.h"
#include "src/Backtracking.h"
#include "src/BuscaLargura.h"
#include "src/BuscaProfundidadeLimitada.h"
#include "src/BuscaOrdenada.h"
#include "src/BuscaGulosa.h"
#include "src/BuscaAEstrela.h"
#include "src/BuscaIDA.h"
#include "src/Algoritmo.h"
using namespace std;

int main()
{
    string file = "Labirintos/lab1.txt";
    fstream log;
    log.open ("log.txt", fstream::app);

    Labirinto *lab = new Labirinto();
    lab->set_labirinto(file);
    
    Backtracking* bt = new Backtracking();
    log << bt->backtracking(*lab);

/*
    BuscaLargura* bl = new BuscaLargura();
    bl->busca_largura(*lab);

    BuscaProfundidadeLimitada* bp = new BuscaProfundidadeLimitada();
    bp->busca_profundidade_limitada(*lab, 50);

    BuscaOrdenada* bo = new BuscaOrdenada();
    bo->buscaOrdenada(*lab);
    
    BuscaGulosa* bg = new BuscaGulosa();
    bg->buscaGulosa(*lab);

    BuscaAEstrela* ba = new BuscaAEstrela();
    ba->buscaAEstrela(*lab);

    BuscaIDA* bIDA = new BuscaIDA();
    bIDA->buscaIDA(*lab);
*/
    return 0;
}
#include "src/Labirinto.h"
#include "src/Backtracking.h"
#include "src/BuscaLargura.h"
#include "src/BuscaProfundidadeLimitada.h"
#include "src/BuscaOrdenada.h"
#include "src/BuscaGulosa.h"
#include "src/BuscaAEstrela.h"
#include "src/BuscaIDA.h"

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
    bp->busca_profundidade_limitada(*lab, 50);

    BuscaOrdenada* bo = new BuscaOrdenada();
    bo->buscaOrdenada(*lab);
    
    BuscaGulosa* bg = new BuscaGulosa();
    bg->buscaGulosa(*lab);

    BuscaAEstrela* ba = new BuscaAEstrela();
    ba->buscaAEstrela(*lab);

    BuscaIDA* bIDA = new BuscaIDA();
    bIDA->buscaIDA(*lab);

    return 0;
}
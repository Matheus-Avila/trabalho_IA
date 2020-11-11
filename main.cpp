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
    Labirinto *lab = new Labirinto();
    //lab->criaLab(50, "lab4.txt");

    fstream log;
    log.open ("Estatisticas/loglab4.txt", fstream::app);

    lab->set_labirinto("Labirintos/lab4.txt");
    
    Backtracking* bt = new Backtracking();
    bt->backtracking(*lab);
    log << bt->getEstatisticas();
    log << '\n';


    BuscaLargura* bl = new BuscaLargura();
    bl->busca_largura(*lab);
    log << bl->getEstatisticas();
    log << '\n';

    BuscaProfundidadeLimitada* bp = new BuscaProfundidadeLimitada();
    bp->busca_profundidade_limitada(*lab, 100);
    log << bp->getEstatisticas();
    log << '\n';
    /*

    BuscaOrdenada* bo = new BuscaOrdenada();
    bo->buscaOrdenada(*lab);
    log << bo->getEstatisticas();
    log << '\n';

    BuscaGulosa* bg = new BuscaGulosa();
    bg->buscaGulosa(*lab);
    log << bg->getEstatisticas();
    log << '\n';

    BuscaAEstrela* ba = new BuscaAEstrela();
    ba->buscaAEstrela(*lab);
    log << ba->getEstatisticas();
    log << '\n';

    BuscaIDA* bIDA = new BuscaIDA();
    bIDA->buscaIDA(*lab);
    log << bIDA->getEstatisticas();
    log << '\n';
*/
    log.close();
    
    return 0;
}
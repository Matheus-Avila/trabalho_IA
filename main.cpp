#include "src/Labirinto.h"
#include "src/Node.h"
#include "src/Algoritmo.h"
#include "src/Backtracking.h"

using namespace std;

int main()
{

    Labirinto *lab = new Labirinto();
    lab->set_labirinto("Labirintos/lab1.txt");

    Backtracking* bt = new Backtracking();
    bt->backtracking(*lab);


    return 0;
}
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "Board.h"
using namespace std;

int main()
{
    srand(time(NULL));   // Initialization, should only be called once.
    int n = 2; //nombre de quasispecies
    vector<float> growthRates = {0 , 1 , 0.5};
    vector<vector<float>> mutations {   { 0.9, 0.1 },
                                        { 0.1, 0.9 }
                                    };
    float diffusion = 0.05;

    int L = 200;
    int h = 10000;
    Board b = Board(L,L, n, growthRates, mutations, diffusion); // initialize random board.
    //b.iteration();
    b.iterate(h);


    return 0;
}

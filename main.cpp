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
    vector<float> growthRates = {0 , 0.3 , 0.1};

    vector<vector<float>> mutations {   { 0.7, 0.3 },  //{ 0.7, 0.3 }, extinsio {0.75, 0.25 comú}
                                        { 0, 1 }
                                    };
    float diffusion = 0.05;

    int L = 200;
    int h = 10000;
    Board b = Board(L,L, n, growthRates, mutations, diffusion); // initialize random board.
    //b.iteration();
    b.iterate(h);


    return 0;
}

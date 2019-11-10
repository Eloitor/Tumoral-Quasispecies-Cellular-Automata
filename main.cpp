#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "Board.h"
#include <fstream>

#define ENOUGH 100
using namespace std;

int main()
{
    /// UNIVERSAL PARAMETERS
    int L = 200;
    int h = 10000;
    float diffusion = 0.05;


    char fileName[ENOUGH] , folderName[ENOUGH];
    sprintf(folderName, "%d", L);

    vector<float> growthRates = {0 , 0.3 , 0.1};

    vector<vector<float>> mutations { { 0.69, 0.31 },  //{ 0.7, 0.3 }, extinsio {0.75, 0.25 comú}
                                        { 0, 1 }
                                    };


    sprintf(fileName, "%.2f_%.2f_%.2f.txt", growthRates[1], growthRates[2], mutations[0][1]);
    FILE *myFile = fopen( fileName, "w" );

    srand(time(NULL));   // Initialization, should only be called once.
    int n = 2; //nombre de quasispecies

    Board b = Board(L,L, n, growthRates, mutations, diffusion, myFile); // initialize random board.
    //b.iteration();
    b.iterate(h);
    fclose(myFile);
    return 0;
}

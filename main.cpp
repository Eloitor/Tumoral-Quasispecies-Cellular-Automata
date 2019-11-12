#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>


#include "Board.h"
#include "bitmap.h"
#define ENOUGH 100

using namespace std;



int main()
{

    int L = 200; //mida del tauler
    int h = 10000;  // nombre total de genracions
    float diffusion = 0.07;  //probabilitat de difussio

    char fileName[ENOUGH];

    vector<float> growthRates = {0 , 0.2 , 0.15 , 0.05}; //Growth rate de les especies (amb un zero al davant, per les cèl·lules buides
    vector<vector<float>> mutations { { 0.75, 0.25, 0},  //Mutació entre quasiespecies
                                        { 0, 0.6, 0.2},
                                        { 0, 0, 1}
                                    };
    sprintf(fileName, "%.2f_%.2f_%.2f.txt", growthRates[1], growthRates[2], mutations[0][1]);
    FILE *myFile = fopen( fileName, "w" );

    srand(time(NULL));
    int n = 3; //nombre de quasispecies

    Board b = Board(L,L, n, growthRates, mutations, diffusion, myFile); // initialize random board.
    b.draw();
    b.iterate(h); // Fer h iteracions

    fclose(myFile);
    return 0;
}

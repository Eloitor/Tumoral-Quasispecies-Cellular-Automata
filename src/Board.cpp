#include "Board.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <time.h>

int mutation(std::vector <float> &probabilities, float random_number){
    float cnt = 0;
    int len = probabilities.size();
    for(int i=0; i< len; i++){
        cnt += probabilities[i];
        if(random_number<cnt)
            return i;
    }
    return len-1;

}

//constructor
Board::Board(int row, int col, int spec, std::vector<float> &growthRate, std::vector<std::vector<float> > &mutations , float diffusion)
{


    board = (int**)malloc( row * sizeof( int* ));
    total=0;
    double newTotalFitness = 0;
    for ( int r = 0; r < row; r++ )
        {
            board[r] = (int*)malloc( col * sizeof( int));
            for(int c=0; c<col; c++){
                int s =rand() % (spec+1); //podem inicialitzar a 0
                board[r][c] = s;
                if(s){
                    total ++;
                    newTotalFitness += growthRate[s];
                }
            }
        }

    this->growthRate = growthRate;
    this->mutations =mutations;
    this->diffusion = diffusion;
    this->counter.resize(spec,0);
    this->row =row;
    this->col = col;
    averageFitness = newTotalFitness/(double) total;
    std::cout<< "Gen " << gen<<":\t" << averageFitness << std::endl;
    totalFitness = newTotalFitness;

}

void Board::iteration(){
    for(int i=0; i<row*col; i++)
    {
        int r = (int)std::rand() % row;
        int c = (int)std::rand() % col;

        if(board[r][c] == 0)
            continue;
        int neighborR=r;
        int neighborC=c;

        int ran = rand() % 8;

        if(ran<=2)
            neighborR = neighborR+row-1;
        if(ran>=5)
            neighborR = neighborR+1;
        if(ran==0 || ran == 3 || ran == 5)
            neighborC = neighborC+col-1;
        if(ran==2 || ran == 4 || ran == 7)
            neighborC = neighborC+1;

        int *neighbor = &(board[neighborR%row][neighborC%col]);

        if(*neighbor ==0 && ((float)rand()/(float)(RAND_MAX)) < averageFitness){
            *neighbor = mutation(mutations[board[r][c] -1], (float)rand()/(float)(RAND_MAX))+1;
            totalFitness+=growthRate[*neighbor];
            total++;
        }

        //degradation
        if(*neighbor !=0 && ((float)rand()/(float)(RAND_MAX)) < growthRate[*neighbor]){
            totalFitness-=growthRate[board[r][c]];
            total--;
            board[r][c] = 0;
        }

        // diffusion
        if(*neighbor !=0 && board[r][c] != 0 && ((float)rand()/(float)(RAND_MAX)) < diffusion){
            std::swap(*neighbor, board[r][c]);
        }
    }
    gen++;
    averageFitness = totalFitness/(double) total;
    std::cout<< "Gen " << gen<<":\t" << averageFitness << std::endl;
   // totalFitness = newTotalFitness;
}

void Board::iterate(int h){
    for(int i=0; i< h; i++){
        iteration();
        if (total ==0)
            break;
    }
}

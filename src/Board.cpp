#include "Board.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include "bitmap.h"

using namespace std;




void Board::report(){


    //averageFitness = newTotalFitness/(double) total;

 //   std::fprintf(myFile,"Gen %3d:\t%f\t%f\t%d/%d\n", gen, averageFitness,(float)totalMaster/(double) total, totalMaster,total );
    if(gen%50 ==0){
       std::printf("Gen %3d:", gen);
        for(int i = 0 ; i< spec+1; i++){
            std::printf("\t%d", totalCount[i] );
        }
        std::printf("\n");
      //  std::printf(myFile,"\t%f\n", averageFitness);
       // draw();
       draw();

    }
    std::fprintf(myFile,"Gen %3d:", gen);
    for(int i = 0 ; i< spec+1; i++){
        std::fprintf(myFile,"\t%d", totalCount[i] );
        // printf("Hello %d\n",i);
    }
    std::fprintf(myFile,"\n");
   // std::fprintf(myFile,"\t%f\n", averageFitness);
    //\t%f\t%f\t%d/%d\n", gen, averageFitness,(float)totalMaster/(double) total , totalMaster,total);
   // std::printf("Gen %3d:\t%f\t%f\t%d/%d\n", gen, averageFitness,(float)totalMaster/(double) total, totalMaster,total );
    //std::cout<< "Gen " << gen<<":\t" << averageFitness << std::endl;
    //totalFitness = newTotalFitness;

}

void Board::draw(){

    //bmp = image.toPixelMatrix();

    for(int r=0; r<row; r++)
    for(int c=0; c<col; c++){
        bmp[r][c] = colors[board[r][c]];

    }


    image.fromPixelMatrix(bmp);
    char fileName[100];
    sprintf(fileName, "img/%05d.bmp",gen);
    image.save(fileName);
}

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
Board::Board(int row, int col, int spec, std::vector<float> &growthRate, std::vector<std::vector<float> > &mutations , float diffusion, std::FILE* myFile)
{

    colors[0] = Pixel(255,255,255); //White
    colors[1] = Pixel(230,25,75); // Red
    colors[2] = Pixel(60,180,75); // Green
    colors[3] = Pixel(255,255,25);  //Yellow
    colors[4] = Pixel(0,130,200);  //Blue
    //colors[5] = Pixel(245,130,48);  //Orange
    colors[5] = Pixel(145,30,180);  //Purple
    this->spec = spec;
    for(int i=0; i< spec+1; i++){
        totalCount[i] = 0;
    }

    bmp.resize(row, std::vector<Pixel>(col, Pixel(255,255,255)));
    this->myFile = myFile;
    total=0;
    double newTotalFitness = 0;

    board = (int**)malloc( row * sizeof( int* ));
    for ( int r = 0; r < row; r++ )
        {
            board[r] = (int*)malloc( col * sizeof( int));
            for(int c=0; c<col; c++){
                int s =rand() % (spec+1); //podem inicialitzar a 0
                board[r][c] = s;
                newTotalFitness += growthRate[s];
                totalCount[s] ++;

            }
        }

    this->growthRate = growthRate;
    this->mutations = mutations; //probabilitats de mutar
    this->diffusion = diffusion;
    this->row =row;
    this->col = col;

    report();

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

        //Select a random neighbor
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

        //Replication + Mutation
        if(*neighbor ==0 && ((float)rand()/(float)(RAND_MAX)) < growthRate[board[r][c]]){
            *neighbor = mutation(mutations[board[r][c] -1], (float)rand()/(float)(RAND_MAX))+1;
            totalFitness+=growthRate[*neighbor];
            total++;
            totalCount[*neighbor]++;
            totalCount[0]--;
        }

        //competence
        if(*neighbor !=0 && ((float)rand()/(float)(RAND_MAX)) < growthRate[*neighbor]){
            totalFitness-=growthRate[board[r][c]];
            total--;
            totalCount[board[r][c]] --;
            totalCount[0]++;
            board[r][c] = 0;
        }

        // diffusion
        if(*neighbor !=0 && board[r][c] != 0 && ((float)rand()/(float)(RAND_MAX)) < diffusion){
            std::swap(*neighbor, board[r][c]);
        }
    }
    gen++;
    report();
    //std::cout<< "Gen " << gen<<":\t" << averageFitness << std::endl;
   // totalFitness = newTotalFitness;
}

void Board::iterate(int h){
    for(int i=0; i< h; i++){
        iteration();
        if (total ==0)
            break;
    }
}

#ifndef BOARD_H
#define BOARD_H
#include<vector>
#include <fstream>
#include "bitmap.h"
class Board
{
    public:
        Board(int row, int col, int spec, std::vector<float> &growthRate, std::vector<std::vector<float> > &mutations , float diffusion, std::FILE* myFile);

        std::FILE* myFile;

        std::vector<float> growthRate;
        std::vector<std::vector<float> > mutations;

        std::vector <std::vector <Pixel> > bmp;
        void iteration();
        void draw();
        Bitmap image;
        int row;
        int col;
        int spec;
        int** board;

        void iterate(int h);
        float diffusion;


        ///Stats
        int total;
        int totalMaster;
        float totalFitness;
        float averageFitness;
        int gen = 0;


    protected:

    private:


};

#endif // BOARD_H

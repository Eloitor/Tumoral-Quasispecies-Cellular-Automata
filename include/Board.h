#ifndef BOARD_H
#define BOARD_H
#include<vector>
class Board
{
    public:
        Board(int row, int col, int spec, std::vector<float> &growthRate, std::vector<std::vector<float> > &mutations , float diffusion);

        std::vector<float> growthRate;
        std::vector<std::vector<float> > mutations;
        std::vector <int> counter;

        void iteration();

        int row;
        int col;
        int spec;
        int** board;
        float totalFitness;
        float averageFitness;
        void iterate(int h);
        float diffusion;

        int total;
        int totalMaster;
        int gen = 0;


    protected:

    private:


};

#endif // BOARD_H

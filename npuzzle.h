#ifndef N_PUZZLE_H
#define N_PUZZLE_H

#include <iostream>
#include <vector>

using namespace std;

class npuzzle {
    private:
        vector<vector<string>> puzzle;
        npuzzle* prev;
        unsigned size;
        unsigned gCost;
        unsigned hCost;
        pair<int, int> blank_loc;
    
    public:
        npuzzle();
        npuzzle(vector<vector<string>>, int);
        ~npuzzle();
        void go_right();
        void go_left();
        void go_up();
        void go_down();
        bool check_right();
        bool check_left();
        bool check_down();
        bool check_up();
        void print_puzzle();
        pair<int,int> findBlank();
};

#endif
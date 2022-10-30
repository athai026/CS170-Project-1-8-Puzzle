#ifndef N_PUZZLE_H
#define N_PUZZLE_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

class npuzzle {
    private:
        vector<vector<string>> puzzle;
        // const npuzzle* prev;
        unsigned size;
        unsigned gCost;
        unsigned hCost;
        unsigned fCost;
        pair<int, int> blank_loc;
        vector<vector<string>> goalPuzzle;
    
    public:
        npuzzle();
        npuzzle(vector<vector<string>>, int);
        npuzzle(const npuzzle&); //copy constructor
        ~npuzzle();
        void go_right();
        void go_left();
        void go_up();
        void go_down();
        bool check_right();
        bool check_left();
        bool check_down();
        bool check_up();
        void print_puzzle() const;
        pair<int,int> findBlank();
        bool isGoal();
        const int get_gCost() const;
        const int get_hCost() const;
        const int get_fCost() const;
        void expand(priority_queue<npuzzle>&);
        void uniformCost(priority_queue<npuzzle>&, vector<npuzzle>&);
        // void misplaced(priority_queue<npuzzle>, vector<npuzzle>&);
        // void manhattan(priority_queue<npuzzle>, vector<npuzzle>&);

        bool operator<(const npuzzle& rhs) const {
            return this->get_fCost() > rhs.get_fCost();
        }

        npuzzle operator=(const npuzzle& rhs) {
            this->puzzle = rhs.puzzle;
            this->size = rhs.size;
            this->gCost = rhs.gCost;
            this->hCost = rhs.hCost;
            this->fCost = rhs.fCost;
            this->blank_loc = rhs.blank_loc;
            this->goalPuzzle = rhs.goalPuzzle;
            
            return *this;
        }
};

// bool operator<(const npuzzle& lhs, const npuzzle& rhs) {
//     cout << "in operator<" << endl;
//     return !(lhs.get_fCost() < rhs.get_fCost());
// }

#endif
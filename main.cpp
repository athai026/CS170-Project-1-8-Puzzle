#include "npuzzle.h"

int main() {

    int puzzle_size;
    string puzzle_nums;
    vector<vector<string>> puzzle;

    cout << "input size n (nxn): ";
    cin >> puzzle_size;

    puzzle.resize(puzzle_size);
    for (int i = 0; i < puzzle_size; ++i) {
        puzzle.at(i).resize(puzzle_size);
    }

    cout << "input puzzle: ";
    cin >> puzzle_nums;

    int k = 0;
    for (int i = 0; i < puzzle_size; ++i) {
        for (int j = 0; j < puzzle_size; ++j) {
            puzzle.at(i).at(j) = puzzle_nums.at(k);
            ++k;
        }
    }

    npuzzle newPuzzle(puzzle, puzzle_size);
    newPuzzle.print_puzzle();
    newPuzzle.go_right();
    newPuzzle.go_down();
    newPuzzle.go_left();
    newPuzzle.go_up();
    newPuzzle.print_puzzle();
    

    // for (int i = 0; i < puzzle_size; ++i) {
    //     for (int j = 0; j < puzzle_size; ++j) {
    //         cout << puzzle.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }



    return 0;
}
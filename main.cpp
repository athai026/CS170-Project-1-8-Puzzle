#include "./npuzzle.h"

// struct compare_fCost {
//     bool operator() (npuzzle child1, npuzzle child2) {
//         return child1.get_fCost() > child2.get_fCost();
//     }
// };

// bool operator<(const npuzzle& lhs, const npuzzle& rhs) {
//     cout << "in operator<" << endl;
//     return !(lhs.get_fCost() < rhs.get_fCost());
// }

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

    for (int i = 0; i < puzzle_size; ++i) {
        cout << "insert values for row " << i+1 << " separated by spaces: ";
        for (int j = 0; j < puzzle_size; ++j) {
            cin >> puzzle_nums;
            puzzle.at(i).at(j) = puzzle_nums;
        }
    }

    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with Misplaced Tile Heuristic" << endl;
    cout << "3. A* with Manhattan Distance Heuristic" << endl;
    cout << "Which search algorithm would you like to use?" << endl;
    cout << "Input the number: ";
    int choice;
    cin >> choice;

    npuzzle newPuzzle(puzzle, puzzle_size);
    newPuzzle.print_puzzle();
    // newPuzzle.go_right();
    // newPuzzle.go_down();
    // newPuzzle.go_left();
    // newPuzzle.go_up();
    // newPuzzle.print_puzzle();
    
    
    // priority_queue <npuzzle, vector<npuzzle>, compare_fCost> pq;
    priority_queue <npuzzle> pq;
    vector<npuzzle> visited;

    // cout << "pushing" << endl;
    pq.push(newPuzzle);
    cout << "pushed initial state" << endl;

    if (choice == 1) {
        newPuzzle.uniformCost(pq, visited);
    }
    // else if (choice == 2) {
    //     newPuzzle.misplaced(pq, visited);
    // }
    // else if (choice == 3) {
    //     newPuzzle.manhattan(pq, visited);
    // }
    // else {
    //     cout << "Invalid choice" << endl;
    // }

    // npuzzle test;
    // cout << "testing queue pop" << endl;
    // while (!pq.empty()) {
        
    //     test = pq.top();
    //     test.print_puzzle();
    //     // pq.top().print_puzzle();
    //     // visited.push_back(test);
    //     pq.pop();
    // }

    cout << "Number of nodes expanded: " << visited.size() << endl;
    cout << "Depth of solution: " << pq.top().get_gCost() << endl;
    cout << "done" << endl;
    


    return 0;
}

// priority_queue <npuzzle, vector<npuzzle>, greater<npuzzle.get_fCost()>> pq;
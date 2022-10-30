#include "./npuzzle.h"
#include "time.h"
#include <iomanip>

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

    int maxQueueSize = 0;

    clock_t start, end;
    start = clock();

    npuzzle newPuzzle(puzzle, puzzle_size);
    newPuzzle.print_puzzle();
    
    priority_queue <npuzzle> pq;
    vector<npuzzle> visited;

    if (choice == 1 || choice == 2 || choice == 3) {
        pq.push(newPuzzle);
        newPuzzle.search(pq, visited, choice, maxQueueSize);
    }
    else {
        cout << "Invalid choice" << endl;
    }

    end = clock();
    float time_elapsed = float(end - start) / float(CLOCKS_PER_SEC);

    cout <<"Time elapsed: " << fixed << time_elapsed << setprecision(5) << " secs" << endl;
    cout << "Maximum size of queue: " << maxQueueSize << endl;
    cout << "Number of nodes expanded: " << visited.size() << endl;
    cout << "Depth of solution: " << pq.top().get_gCost() << endl;

    return 0;
}


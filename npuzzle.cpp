#include "npuzzle.h"

npuzzle::npuzzle() {
    // prev = NULL;
    size = 0;
    gCost = 0;
    hCost = 0;
    fCost = gCost + hCost;
    blank_loc = make_pair(0,0);
    goalPuzzle.resize(size);
    for (int i = 0; i < size; ++i) {
        goalPuzzle.at(i).resize(size);
    }
}

npuzzle::npuzzle(vector<vector<string>> in, int puzzle_size) {
    puzzle = in;
    size = puzzle_size;
    // prev = NULL;
    gCost = 0;
    hCost = 0;
    fCost = gCost + hCost;
    blank_loc = findBlank();
    goalPuzzle.resize(size);
    for (int i = 0; i < size; ++i) {
        goalPuzzle.at(i).resize(size);
    }

    int goalNum = 1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == size - 1 && j == size -1) {
                goalPuzzle.at(i).at(j) = "0";
            }
            else{
                goalPuzzle.at(i).at(j) = to_string(goalNum);
                ++goalNum;
            }
        }
    }
}

npuzzle::npuzzle(const npuzzle& p1) {
    // prev = &p1;    
    puzzle = p1.puzzle;
    size = p1.size;
    gCost = p1.gCost;
    hCost = p1.hCost;
    fCost = p1.fCost;
    blank_loc = p1.blank_loc;
    goalPuzzle = p1.goalPuzzle;
}

npuzzle::~npuzzle() {
    /*if (prev != nullptr) {
        delete prev;
    }*/
}

void npuzzle::go_right() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    // if (check_right()) {
    //     cout << "you can go right" << endl;
        swap(puzzle.at(i).at(j), puzzle.at(i).at(j + 1));
        blank_loc.second += 1;
        ++gCost;
        ++fCost;
        // print_puzzle();
        // cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        // cout << "testing blank:" << endl;
        // pair <int,int> testBlank = findBlank();
        // isGoal();
    // }
    // else{
    //     cout << "you cannot go right" << endl;
    // }
}

void npuzzle::go_left() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    // if (check_left()) {
    //     cout << "you can go left" << endl;
        swap(puzzle.at(i).at(j), puzzle.at(i).at(j - 1));
        blank_loc.second -= 1;
        ++gCost;
        ++fCost;
        // print_puzzle();
        // cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        // cout << "testing blank:" << endl;
        // pair <int,int> testBlank = findBlank();
    //     isGoal();
    // }
    // else {
    //     cout << "you cannot go left" << endl;
    // }
}

void npuzzle::go_up() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    // if (check_up()) {
    //     cout << "you can go up" << endl;
        swap(puzzle.at(i).at(j), puzzle.at(i - 1).at(j));
        blank_loc.first -= 1;
        ++gCost;
        ++fCost;
        // print_puzzle();
        // cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        // cout << "testing blank:" << endl;
        // pair <int,int> testBlank = findBlank();
    //     isGoal();
    // }
    // else {
    //     cout << "you cannot go up" << endl;
    // }
}

void npuzzle::go_down() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    // if (check_down()) {
    //     cout << "you can go down" << endl;
        swap(puzzle.at(i).at(j), puzzle.at(i + 1).at(j));
        blank_loc.first += 1;
        ++gCost;
        ++fCost;
        // print_puzzle();
        // cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        // cout << "testing blank:" << endl;
        // pair <int,int> testBlank = findBlank();
    //     isGoal();
    // }
    // else{
    //     cout << "you cannot go down" << endl;
    // }
}

bool npuzzle::check_right() {
    if (blank_loc.second != size - 1) {
        return true;
    }
    return false;
}

bool npuzzle::check_left() {
    if (blank_loc.second != 0) {
        return true;
    }
    return false;
}

bool npuzzle::check_down() {
    if (blank_loc.first != size - 1) {
        return true;
    }
    return false;
}

bool npuzzle::check_up(){
    if (blank_loc.first != 0) {
        return true;
    }
    return false;
}

void npuzzle::print_puzzle() const {
    for (int i=  0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << puzzle.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

pair<int,int> npuzzle::findBlank() {
    pair<int,int> blank = make_pair(-1,-1);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (puzzle.at(i).at(j) == "0") {
                pair<int,int> blank = make_pair(i,j);
                cout << "findBlank at (" << i << "," << j << ")" << endl;
                return blank;
            }
        }
    }

    return blank;
}

bool npuzzle::isGoal() {
    if (puzzle == goalPuzzle) {
        cout << "Congratulations!! You have the goal state" << endl;
        return true;
    }
    cout << "not goal state. keep going" << endl;
    return false;
}

const int npuzzle::get_gCost() const {
    return gCost;
}

const int npuzzle::get_hCost() const {
    return hCost;
}

const int npuzzle::get_fCost() const {
    return fCost;
}

void npuzzle::uniformCost(priority_queue<npuzzle>& pq, vector<npuzzle>& visited) {
    cout << "called uniformCost" << endl;
    npuzzle moveRight = pq.top();
    npuzzle moveLeft = pq.top();
    npuzzle moveUp = pq.top();
    npuzzle moveDown = pq.top();

    if (moveRight.check_right()) {
        moveRight.go_right();
        pq.push(moveRight);
    }
    if (moveLeft.check_left()) {
        moveLeft.go_left();
        pq.push(moveLeft);
    }
    if (moveDown.check_down()) {
        moveDown.go_down();
        pq.push(moveDown);
    }
    if (moveUp.check_up()) {
        moveUp.go_up();
        pq.push(moveUp);
    }

    // moveRight.go_right();
    // moveLeft.go_left();
    // moveUp.go_up();
    // moveDown.go_down();

    pq.pop();
    // pq.push(moveRight);
    // pq.push(moveLeft);
    // pq.push(moveUp);
    // pq.push(moveDown);

    npuzzle curr = pq.top();
    visited.push_back(curr);

    if (curr.puzzle != curr.goalPuzzle) {
        uniformCost(pq, visited);
    }
    else {
        cout << "You've reached your goal!" << endl;
        curr.print_puzzle();
    }

}

// void npuzzle::misplaced(priority_queue<npuzzle> pq, vector<npuzzle>& visited) {

// }

// void npuzzle::manhattan(priority_queue<npuzzle> pq, vector<npuzzle>& visited){

// }
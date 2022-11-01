#include "npuzzle.h"

npuzzle::npuzzle() {
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
    puzzle = p1.puzzle;
    size = p1.size;
    gCost = p1.gCost;
    hCost = p1.hCost;
    fCost = p1.fCost;
    blank_loc = p1.blank_loc;
    goalPuzzle = p1.goalPuzzle;
}

npuzzle::~npuzzle() {
}

void npuzzle::go_right(int choice) {
    int i = blank_loc.first;
    int j = blank_loc.second;
    
    swap(puzzle.at(i).at(j), puzzle.at(i).at(j + 1));
    blank_loc.second += 1;
    ++gCost;

    if (choice == 2) {
        hCost = find_misplaced();
    }
    else if (choice == 3) {
        hCost = manhattan_distance();
    }

    fCost = calc_fCost();
}

void npuzzle::go_left(int choice) {
    int i = blank_loc.first;
    int j = blank_loc.second;
    
    swap(puzzle.at(i).at(j), puzzle.at(i).at(j - 1));
    blank_loc.second -= 1;
    ++gCost;

    if (choice == 2) {
        hCost = find_misplaced();
    }
    else if (choice == 3) {
        hCost = manhattan_distance();
    }

    fCost = calc_fCost();
}

void npuzzle::go_up(int choice) {
    int i = blank_loc.first;
    int j = blank_loc.second;

    swap(puzzle.at(i).at(j), puzzle.at(i - 1).at(j));
    blank_loc.first -= 1;
    ++gCost;
    
    if (choice == 2) {
        hCost = find_misplaced();
    }
    else if (choice == 3) {
        hCost = manhattan_distance();
    }

    fCost = calc_fCost();
}

void npuzzle::go_down(int choice) {
    int i = blank_loc.first;
    int j = blank_loc.second;

    swap(puzzle.at(i).at(j), puzzle.at(i + 1).at(j));
    blank_loc.first += 1;
    ++gCost;

    if (choice == 2) {
        hCost = find_misplaced();
    }
    else if (choice == 3) {
        hCost = manhattan_distance();
    }

    fCost = calc_fCost();
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
        cout << "[";
        for (int j = 0; j < size; ++j) {
            cout << puzzle.at(i).at(j);
            if (j != size - 1) {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
    cout << endl;
}

pair<int,int> npuzzle::findBlank() {
    pair<int,int> blank = make_pair(-1,-1);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (puzzle.at(i).at(j) == "0") {
                pair<int,int> blank = make_pair(i,j);
                return blank;
            }
        }
    }

    return blank;
}

bool npuzzle::isGoal() {
    if (puzzle == goalPuzzle) {
        return true;
    }
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

int npuzzle::calc_fCost() {
    return this->gCost + this->hCost;
}

int npuzzle::find_misplaced() {
    int numMisplaced = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (puzzle.at(i).at(j) != "0") {
                if (puzzle.at(i).at(j) != goalPuzzle.at(i).at(j)) {
                    ++numMisplaced;
                }
            }
        }
    }

    return numMisplaced;
}

int npuzzle::manhattan_distance() {
    int manDist = 0;
    int total_heuristic = 0;
    pair<int,int> goalPos;
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (puzzle.at(i).at(j) != "0") {
                if (puzzle.at(i).at(j) != goalPuzzle.at(i).at(j)) {
                    goalPos = findNum(puzzle.at(i).at(j));
                    manDist = abs(i - goalPos.first) + abs(j - goalPos.second);

                    total_heuristic += manDist;
                }
            }
        }
    }

    return total_heuristic;
}


pair<int,int> npuzzle::findNum(string goalNum){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (goalPuzzle.at(i).at(j) == goalNum) {
                return make_pair(i,j);
            }
        }
    }
}

void npuzzle::expand(priority_queue<npuzzle>& pq, int choice) {
    npuzzle moveRight = pq.top();
    npuzzle moveLeft = pq.top();
    npuzzle moveUp = pq.top();
    npuzzle moveDown = pq.top();

    pq.pop();

    if (moveRight.check_right()) {
        moveRight.go_right(choice);
        pq.push(moveRight);
    }
    if (moveLeft.check_left()) {
        moveLeft.go_left(choice);
        pq.push(moveLeft);
    }
    if (moveDown.check_down()) {
        moveDown.go_down(choice);
        pq.push(moveDown);
    }
    if (moveUp.check_up()) {
        moveUp.go_up(choice);
        pq.push(moveUp);
    }
}

void npuzzle::search(priority_queue<npuzzle>& pq, vector<npuzzle>& visited, int choice, int& maxQueueSize) {
    while (!pq.empty()) {
        cout << "The best state to expand with a g(n) = " << pq.top().get_gCost() << " and h(n) = " << pq.top().get_hCost() << " is:" <<endl;
        npuzzle curr = pq.top();
        curr.print_puzzle();
        bool found = false;

        if (curr.isGoal() == false) {
            expand(pq, choice);
            for (int i = 0; i < visited.size(); ++i) {
                if (curr.puzzle == visited.at(i).puzzle) {
                    if (curr.fCost < visited.at(i).fCost) {
                        swap(visited.at(i), curr);
                        found = true;
                        break;
                    }
                    else {
                        found = true;
                        break;
                    }
                }
            }
            if (found == false) {
                visited.push_back(curr);
            }
            
            if (visited.size() > maxQueueSize) {
                maxQueueSize = pq.size();
            }
        }
        else {
            cout << "You've reached your goal!" << endl;
            curr.print_puzzle();
            break;
        }
    }
}
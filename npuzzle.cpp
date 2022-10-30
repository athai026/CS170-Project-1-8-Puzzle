#include "npuzzle.h"

npuzzle::npuzzle() {
    prev = NULL;
    size = 0;
    gCost = 0;
    hCost = 0;
    blank_loc = make_pair(0,0);
}

npuzzle::npuzzle(vector<vector<string>> in, int puzzle_size) {
    puzzle = in;
    size = puzzle_size;
    prev = NULL;
    gCost = 0;
    hCost = 0;
    blank_loc = findBlank();
}

npuzzle::~npuzzle() {
    delete prev;
}

void npuzzle::go_right() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    if (check_right()) {
        cout << "you can go right" << endl;
        string temp = puzzle.at(i).at(j + 1);
        puzzle.at(i).at(j) = temp;
        puzzle.at(i).at(j + 1) = "0";
        blank_loc.second += 1;
        print_puzzle();
        cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        cout << "testing blank:" << endl;
        pair <int,int> testBlank = findBlank();
    }
    else{
        cout << "you cannot go right" << endl;
    }
}

void npuzzle::go_left() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    if (check_left()) {
        cout << "you can go left" << endl;
        string temp = puzzle.at(i).at(j - 1);
        puzzle.at(i).at(j) = temp;
        puzzle.at(i).at(j - 1) = "0";
        blank_loc.second -= 1;
        print_puzzle();
        cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        cout << "testing blank:" << endl;
        pair <int,int> testBlank = findBlank();
    }
    else {
        cout << "you cannot go left" << endl;
    }
}

void npuzzle::go_up() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    if (check_up()) {
        cout << "you can go up" << endl;
        string temp = puzzle.at(i - 1).at(j);
        puzzle.at(i).at(j) = temp;
        puzzle.at(i - 1).at(j) = "0";
        blank_loc.first -= 1;
        print_puzzle();
        cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        cout << "testing blank:" << endl;
        pair <int,int> testBlank = findBlank();
    }
    else {
        cout << "you cannot go up" << endl;
    }
}

void npuzzle::go_down() {
    int i = blank_loc.first;
    int j = blank_loc.second;
    if (check_down()) {
        cout << "you can go down" << endl;
        string temp = puzzle.at(i + 1).at(j);
        puzzle.at(i).at(j) = temp;
        puzzle.at(i + 1).at(j) = "0";
        blank_loc.first += 1;
        print_puzzle();
        cout << "manualBlank at (" << blank_loc.first << "," << blank_loc.second << ")" << endl;
        cout << "testing blank:" << endl;
        pair <int,int> testBlank = findBlank();
    }
    else{
        cout << "you cannot go down" << endl;
    }
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

void npuzzle::print_puzzle(){
    for (int i=  0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << puzzle.at(i).at(j) << " ";
        }
        cout << endl;
    }
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
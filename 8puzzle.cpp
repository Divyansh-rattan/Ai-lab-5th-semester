#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

typedef vector<vector<int>> matrix;
typedef vector<int> position;

// Function to print the puzzle
void display(matrix board) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
           cout << board[i][j] << " ";
        }
        cout << '\n';
    }
}

// Function to check if two boards are same
bool isSame(matrix a, matrix b) {
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < a[0].size(); j++) {
            if(a[i][j] != b[i][j])
                return false;
        }
    }
    return true;
}

// Function to swap positions and return new puzzle
matrix makeMove(matrix board, position from, position to) {
    board[from[0]][from[1]] = board[to[0]][to[1]];
    board[to[0]][to[1]] = 0;
    return board;
}

// Function to find location of 0
vector<int> findBlank(matrix board) {
    position pos = {-1, -1};
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(board[i][j] == 0) {
                pos[0] = i;
                pos[1] = j;
            }
        }
    }
    return pos;
}

// Function to generate possible next boards
vector<matrix> genChildren(matrix node) {
    position position_zero = findBlank(node);
    position position_swap = {-1,-1};
    vector<matrix> children;

    // Left move
    if(position_zero[1] - 1 >= 0){
        position_swap[0] = position_zero[0];
        position_swap[1] = position_zero[1] - 1;
        children.push_back(makeMove(node, position_zero, position_swap));
    }

    // Right move
    if(position_zero[1] + 1 < node[0].size()){
        position_swap[0] = position_zero[0];
        position_swap[1] = position_zero[1] + 1;
        children.push_back(makeMove(node, position_zero, position_swap));
    }

    // Upper move
    if(position_zero[0] - 1 >= 0){
        position_swap[0] = position_zero[0] - 1;
        position_swap[1] = position_zero[1];
        children.push_back(makeMove(node, position_zero, position_swap));
    }

    // Down move
    if(position_zero[0] + 1 < node.size()){
        position_swap[0] = position_zero[0] + 1;
        position_swap[1] = position_zero[1];
        children.push_back(makeMove(node, position_zero, position_swap));
    }

    return children;    
}

// Check if board is already seen
bool alreadyVisited(matrix board, vector<matrix> visitedList) {
    for(int i = 0; i < visitedList.size(); i++) {
        if(isSame(board, visitedList[i])) {
            return true;
        }
    }
    return false;
}

// DFS function to solve puzzle
void solvePuzzle(matrix givenPuzzle, matrix goalPuzzle) {
    stack<matrix> toVisit;
    toVisit.push(givenPuzzle);
    vector<matrix> checkedBoards;
    matrix current;

    while(!toVisit.empty()) {
        current = toVisit.top();
        toVisit.pop();

        if(isSame(current, goalPuzzle)) {
            cout << " solved puzzle is  : \n";
            display(current);
            return;
        }

        vector<matrix> nextSteps = genChildren(current);
        checkedBoards.push_back(current);

        for(int i = 0; i < nextSteps.size(); i++) {
            if(!alreadyVisited(nextSteps[i], checkedBoards))
                toVisit.push(nextSteps[i]);
        }
    }

    cout << "unable to solve \n";
}

// Main function
int main() {
    matrix goalPuzzle = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    matrix givenPuzzle = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 7, 8}
    };

    solvePuzzle(givenPuzzle, goalPuzzle);

    return 0;
}

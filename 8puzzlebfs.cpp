#include <iostream>
#include <vector>
#include <queue> 
#include <set>   
#include <map>   
#include <algorithm>
#include <cmath>

using namespace std;


typedef vector<vector<int>> matrix;
typedef vector<int> position;


string matrixToString(const matrix& board) {
    string s = "";
    for (const auto& row : board) {
        for (int val : row) {
            s += to_string(val);
        }
    }
    return s;
}


void display(const matrix& board) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
           cout << board[i][j] << " ";
        }
        cout << '\n';
    }
}


bool isSame(const matrix& a, const matrix& b) {
    return matrixToString(a) == matrixToString(b);
}


matrix makeMove(matrix board, const position& from, const position& to) {
    swap(board[from[0]][from[1]], board[to[0]][to[1]]);
    return board;
}


position findBlank(const matrix& board) {
    position pos = {-1, -1};
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(board[i][j] == 0) {
                pos[0] = i;
                pos[1] = j;
                return pos;
            }
        }
    }
    return pos;
}

vector<matrix> genChildren(const matrix& node) {
    position position_zero = findBlank(node);
    int r = position_zero[0];
    int c = position_zero[1];
    vector<matrix> children;

   
    vector<pair<int, int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
    
    int board_size = node.size();

    for (const auto& move : moves) {
        int nr = r + move.first;
        int nc = c + move.second;

        
        if (nr >= 0 && nr < board_size && nc >= 0 && nc < board_size) {
            position position_swap = {nr, nc};
            children.push_back(makeMove(node, position_zero, position_swap));
        }
    }

    return children;    
}


void solvePuzzle(const matrix& givenPuzzle, const matrix& goalPuzzle) {
    
    queue<matrix> toVisit; 
    set<string> visited;
    map<string, string> parentMap;
    
    string startString = matrixToString(givenPuzzle);
    string goalString = matrixToString(goalPuzzle);
    
    toVisit.push(givenPuzzle);
    visited.insert(startString);

    cout << "Starting BFS search...\n";
    
    while(!toVisit.empty()) {
        matrix current = toVisit.front();
        toVisit.pop();

        string currentString = matrixToString(current);

        
        if(currentString == goalString) {
            cout << "\n✅ Goal reached! Tracing path...\n";
            
           
            vector<matrix> path;
            matrix temp = goalPuzzle;
            string tempString = goalString;
            
          
            while (tempString != startString) {
                path.push_back(temp);
                tempString = parentMap[tempString];
                
              
                matrix parent(3, vector<int>(3));
                for(int i=0; i<9; ++i) {
                    parent[i/3][i%3] = tempString[i] - '0';
                }
                temp = parent;
            }
            path.push_back(givenPuzzle);
            
            
            reverse(path.begin(), path.end());
            cout << "Path (Total Steps: " << path.size() - 1 << "):\n";
            for(size_t i = 0; i < path.size(); ++i) {
                cout << "Step " << i << ":\n";
                display(path[i]);
            }
            
            return;
        }

     
        vector<matrix> nextSteps = genChildren(current);

        for(const matrix& next : nextSteps) {
            string nextString = matrixToString(next);
            
        
            if(visited.find(nextString) == visited.end()) {
                visited.insert(nextString);
                toVisit.push(next);
               
                parentMap[nextString] = currentString;
            }
        }
    }

    cout << "\n Unable to solve. Goal state is unreachable.\n";
}


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

    cout << "Initial Puzzle:\n";
    display(givenPuzzle);
    cout << "\nGoal Puzzle:\n";
    display(goalPuzzle);
    cout << "\n" << string(40, '-') << "\n";

    solvePuzzle(givenPuzzle, goalPuzzle);

    return 0;
}
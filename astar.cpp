#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>
#include <set>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

struct Node {
    double f, g;
    pair<int, int> pos;
    vector<pair<int, int>> path;

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// Heuristic (Euclidean distance)
double heuristic(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// A* Search
pair<vector<pair<int, int>>, double> a_star(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<tuple<int, int, double>> directions = {
        {-1, 0, 1}, {1, 0, 1}, {0, -1, 1}, {0, 1, 1},
        {-1, -1, 1.5}, {-1, 1, 1.5}, {1, -1, 1.5}, {1, 1, 1.5}
    };

    priority_queue<Node, vector<Node>, greater<Node>> open_set;
    set<pair<int, int>> visited;

    open_set.push({heuristic(start, goal), 0, start, {start}});

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        if (visited.count(current.pos)) continue;
        visited.insert(current.pos);

        if (current.pos == goal) {
            return {current.path, current.g};
        }

        for (auto& dir : directions) {
            int dx = get<0>(dir);
            int dy = get<1>(dir);
            double cost = get<2>(dir);

            int nx = current.pos.first + dx;
            int ny = current.pos.second + dy;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1) {
                if (!visited.count({nx, ny})) {
                    double new_g = current.g + cost;
                    double new_f = new_g + heuristic({nx, ny}, goal);
                    vector<pair<int, int>> new_path = current.path;
                    new_path.push_back({nx, ny});
                    open_set.push({new_f, new_g, {nx, ny}, new_path});
                }
            }
        }
    }

    return {{}, numeric_limits<double>::infinity()}; // No path
}

// Console visualization
void visualize(vector<vector<int>>& grid, vector<pair<int, int>>& path, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    for (size_t step = 0; step < path.size(); step++) {
#ifdef _WIN32
        system("cls");  // Windows
#else
        system("clear"); // Linux/Mac
#endif

        vector<vector<char>> display(rows, vector<char>(cols, ' '));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) display[i][j] = '~'; // river
                else display[i][j] = '.'; // land
            }
        }

        for (size_t k = 0; k <= step; k++) {
            display[path[k].first][path[k].second] = 'o'; // path
        }

        display[start.first][start.second] = 'S'; // start
        display[goal.first][goal.second] = 'E';   // goal

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << display[i][j] << " ";
            }
            cout << "\n";
        }

        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    int n, m;
    cout << "Enter grid size (rows cols): ";
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    cout << "Enter grid row by row (0 = river, 1 = land):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];

    int sx, sy, gx, gy;
    cout << "Enter start position (row col): ";
    cin >> sx >> sy;
    cout << "Enter goal position (row col): ";
    cin >> gx >> gy;

    pair<int, int> start = {sx, sy}, goal = {gx, gy};

    auto result = a_star(grid, start, goal);
    vector<pair<int, int>> path = result.first;
    double cost = result.second;

    if (!path.empty()) {
        cout << "Path found! Cost = " << cost << "\n";
        visualize(grid, path, start, goal);
    } else {
        cout << "No path found.\n";
    }

    return 0;
}

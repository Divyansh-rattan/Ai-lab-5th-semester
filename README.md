1->the 8-puzzle problem using two search algorithms — Depth First Search (DFS) and Breadth First Search (BFS).
The puzzle is a 3x3 grid where numbers 1–8 are arranged, and one blank space (0) can move up, down, left, or right.
The goal is to move the tiles to reach the final target arrangement.
2->How It Works
The puzzle is represented as a matrix using vector<vector<int>>.
The blank tile (0) moves in four directions to create new states.
The program keeps track of visited states to avoid repeating them.
It checks each state until the goal configuration is found.
3->Algorithms Used
DFS (Depth First Search):
Explores one path deeply before backtracking. It can solve the puzzle but may not find the shortest path.
BFS (Breadth First Search):
Explores level by level and always finds the shortest path to the goal. It also shows each step from start to goal.
4->Time complexity
DFS: Time complexity is O(N²) because each new state checks all visited boards linearly, and space complexity is O(N) for storing visited states.
BFS: Time complexity is O(N) since each state is processed once with efficient set/map lookups, and space complexity is also O(N) for storing visited nodes and paths.

#pragma once
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

class Maze {
public:
    Maze(int width, int height);

    const std::vector<std::vector<int>>& getMaze() const;


private:
    std::vector<std::vector<int>> mazeGrid;

    void generateMaze(int width, int height);
};

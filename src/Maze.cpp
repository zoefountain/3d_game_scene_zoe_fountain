#include <./include/Maze.h>

Maze::Maze(int width, int height)
{
	generateMaze(width, height);
}

void Maze::generateMaze(int width, int height)
{
    mazeGrid.resize(width, std::vector<int>(height, 0));
    for (int x = 0; x < width; ++x) 
    {
        for (int y = 0; y < height; ++y) 
        {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1 || (x % 2 == 0 && y % 2 == 0)) 
            {
                mazeGrid[x][y] = 1; // Wall
            }
            else 
            {
                mazeGrid[x][y] = 0; // Path
            }
        }
    }
}

const std::vector<std::vector<int>>& Maze::getMaze() const 
{
    return mazeGrid;
}

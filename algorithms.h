#ifndef ALGO_H
#define ALGO_H

#include "grid.h"
#include <vector>

class Algorithms {
public:
    static std::vector<Cell*> BFS(Grid& grid, Cell* start, Cell* end);
    static std::vector<Cell*> DFS(Grid& grid, Cell* start, Cell* end);
    static std::vector<Cell*> Dijkstra(Grid& grid, Cell* start, Cell* end);
    static std::vector<Cell*> AStar(Grid& grid, Cell* start, Cell* end);
};

#endif

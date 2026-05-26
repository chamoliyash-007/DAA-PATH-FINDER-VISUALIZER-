#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>

const int ROWS = 20;
const int COLS = 20;
const int CELL_SIZE = 30;

enum CellType { EMPTY, WALL, START, END, VISITED, PATH };

struct Cell {
    int row, col;
    CellType type;
};

class Grid {
public:
    std::vector<std::vector<Cell>> grid;

    Grid();
    void draw(sf::RenderWindow& window);
    void handleClick(int x, int y);
    Cell& getCell(int r, int c);
};

#endif

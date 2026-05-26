#include "grid.h"

Grid::Grid() {
    grid.resize(ROWS, std::vector<Cell>(COLS));
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = {i, j, EMPTY};
}

void Grid::draw(sf::RenderWindow& window) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            sf::RectangleShape rect({CELL_SIZE - 1.f, CELL_SIZE - 1.f});
            rect.setPosition({j * CELL_SIZE * 1.f, i * CELL_SIZE * 1.f});

            switch (grid[i][j].type) {
                case EMPTY: rect.setFillColor(sf::Color::White); break;
                case WALL: rect.setFillColor(sf::Color::Black); break;
                case START: rect.setFillColor(sf::Color::Green); break;
                case END: rect.setFillColor(sf::Color::Red); break;
                case VISITED: rect.setFillColor(sf::Color::Blue); break;
                case PATH: rect.setFillColor(sf::Color::Yellow); break;
            }

            window.draw(rect);
        }
    }
}

void Grid::handleClick(int x, int y) {
    int c = x / CELL_SIZE;
    int r = y / CELL_SIZE;

    if (r >= ROWS || c >= COLS) return;

    if (grid[r][c].type == EMPTY)
        grid[r][c].type = WALL;
    else if (grid[r][c].type == WALL)
        grid[r][c].type = EMPTY;
}

Cell& Grid::getCell(int r, int c) {
    return grid[r][c];
}
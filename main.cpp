#include <SFML/Graphics.hpp>
#include <optional>
#include <thread>
#include <chrono>
#include <iostream>
#include "grid.h"
#include "algorithms.h"

int main() {

    sf::RenderWindow window(
        sf::VideoMode({COLS * CELL_SIZE, ROWS * CELL_SIZE}),
        "Pathfinding Visualizer"
    );

    Grid grid;

    Cell* start = &grid.getCell(0, 0);
    Cell* end = &grid.getCell(ROWS - 1, COLS - 1);

    start->type = START;
    end->type = END;

    std::vector<Cell*> path;

    int selectedAlgo = 0; // 1=BFS, 2=DFS, 3=Dijkstra, 4=A*

    while (window.isOpen()) {

        while (const std::optional<sf::Event> event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (auto m = event->getIf<sf::Event::MouseButtonPressed>())
                    grid.handleClick(m->position.x, m->position.y);
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (auto k = event->getIf<sf::Event::KeyPressed>()) {

                    if (k->code == sf::Keyboard::Key::Num1) {
                        selectedAlgo = 1;
                        std::cout << "BFS Selected\n";
                    }
                    if (k->code == sf::Keyboard::Key::Num2) {
                        selectedAlgo = 2;
                        std::cout << "DFS Selected\n";
                    }
                    if (k->code == sf::Keyboard::Key::Num3) {
                        selectedAlgo = 3;
                        std::cout << "Dijkstra Selected\n";
                    }
                    if (k->code == sf::Keyboard::Key::Num4) {
                        selectedAlgo = 4;
                        std::cout << "A* Selected\n";
                    }
                    if (k->code == sf::Keyboard::Key::Enter && selectedAlgo != 0) {

                        // Clear old path
                        for (int i = 0; i < ROWS; i++) {
                            for (int j = 0; j < COLS; j++) {
                                if (grid.getCell(i, j).type == VISITED ||
                                    grid.getCell(i, j).type == PATH)
                                    grid.getCell(i, j).type = EMPTY;
                            }
                        }

                        // Run selected algorithm
                        if (selectedAlgo == 1)
                            path = Algorithms::BFS(grid, start, end);

                        if (selectedAlgo == 2)
                            path = Algorithms::DFS(grid, start, end);

                        if (selectedAlgo == 3)
                            path = Algorithms::Dijkstra(grid, start, end);

                        if (selectedAlgo == 4)
                            path = Algorithms::AStar(grid, start, end);

                        for (auto cell : path) {
                            if (cell->type != START && cell->type != END) {
                                cell->type = PATH;

                                window.clear();
                                grid.draw(window);
                                window.display();

                                std::this_thread::sleep_for(
                                    std::chrono::milliseconds(20));
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
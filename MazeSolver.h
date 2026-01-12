#pragma once

#include "Maze.h"
#include <vector>
#include <utility> // для std::pair
using namespace std;

// Паттерн "Стратегия"
// Интерфейс для алгоритмов поиска пути (можно сделать DFS, BFS, A*)

class MazeSolver {
public:
    virtual ~MazeSolver() = default;
    // Метод принимает лабиринт, старт и финиш. Возвращает список координат пути.
    virtual vector<pair<int,int>> solve(
        Maze* maze,
        pair<int,int> start,
        pair<int,int> end) = 0;
};

// Конкретная стратегия: Поиск в ширину (BFS)
class BFSSolver : public MazeSolver {
public:
    vector<pair<int, int>> solve(
        Maze *maze,
        pair<int, int> start,
        pair<int, int> end) override;
};
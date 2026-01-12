#include "MazeSolver.h"
#include <algorithm>
#include <queue>
//логика прохождения (поиск кратчайшего пути) 
vector<pair<int, int> > BFSSolver::solve(Maze *maze, pair<int, int> start, pair<int, int> end) {
    int rows = maze->getGrid().size();
    int cols = rows;

    // Сразу проверяем: если старт или финиш в стене, пути нет
    if (maze->isWall(start.first, start.second) ||
        maze->isWall(end.first, end.second)) {
        return {}; // Возвращаем пустой путь
    }

    // Массив parent хранит "откуда мы пришли" в клетку [i][j].
    // Нужен для восстановления пути назад. {-1, -1} значит не посещена.
    vector<vector<pair<int, int>>> parent(
        rows, vector<pair<int, int>>(cols, {-1, -1}));

    queue<pair<int, int>> q; // Очередь клеток для проверки
    q.push(start);
    parent[start.first][start.second] = {-2, -2}; // Маркер старта (чтобы не зациклиться)

    // Направления движения: вправо, влево, вниз, вверх
    vector<pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    bool found = false;

    //Волновой алгоритм
    while (!q.empty()) {
        auto [currR, currC] = q.front(); // Берем первую клетку из очереди
        q.pop();

        // Если дошли до финиша
        if (currR == end.first && currC == end.second) {
            found = true;
            break;
        }

        // Проверяем 4 соседние клетки
        for (const auto& dir : directions) {
            int nr = currR + dir.first;
            int nc = currC + dir.second;

            // Проверка: координаты валидны, это не стена, и мы там еще не были
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                maze->isPath(nr, nc) &&
                parent[nr][nc].first == -1) {

                parent[nr][nc] = {currR, currC}; // Запоминаем родителя
                q.push({nr, nc}); // Добавляем в очередь
            }
        }
    }

    //Восстановление пути
    vector<pair<int, int>> path;
    if (found) {
        pair<int, int> curr = end;
        // Идем от финиша к старту по родителям
        while (curr.first != -2) { 
            path.push_back(curr);
            curr = parent[curr.first][curr.second];
        }
        reverse(path.begin(), path.end()); // Разворачиваем путь, чтобы был от старта к финишу
    }

    return path;
}

#include "MazeGenerator.h"
#include <algorithm>
#include <random>
//логика создания лабиринта
// Функция возвращает true/false с вероятностью 50%
bool EllerMazeGenerator::randomBool() {
    static random_device rd; // Источник энтропии
    static mt19937 gen(rd()); // Вихрь Мерсенна (качественный генератор)
    static uniform_int_distribution<int> dis(0, 1);
    return dis(gen) == 1;
}

// Генерация лабиринта Эллера (построчный алгоритм)
Maze *EllerMazeGenerator::generate(unsigned int size) {
    Maze* maze = new Maze(size); // Создаем пустой лабиринт (все стены)
    auto& grid = const_cast<vector<vector<int>>&>(maze->getGrid());
    vector<int> rowSet(size, 0);//хранит номер множества для каждой ячейки текущей строки.
    int nextSetId = 1; // Сквозной счетчик множеств

    // Цикл по всем строкам лабиринта
    for (int row = 0; row < size; ++row) {
        
        //Присвоить множества пустым ячейкам
        for (int col = 0; col < size; ++col) {
            if (rowSet[col] == 0) {
                rowSet[col] = nextSetId++; // Новое уникальное множество
            }
            grid[2 * row + 1][2 * col + 1] = 0; // Делаем эту клетку проходом
        }

        //Создание правых границ (объединение множеств)
        for (int col = 0; col < size - 1; ++col) {
            bool addWall = randomBool(); // Случайно решаем, ставить стену или нет

            // Если ячейки уже в одном множестве -> обязана быть стена
            // Если это последняя строка -> стены ломаем, чтобы соединить все части
            if (rowSet[col] == rowSet[col + 1] || 
                (row == size - 1 && rowSet[col] != rowSet[col + 1])) {
                addWall = true; // Принудительная стена
                if (row == size - 1 && rowSet[col] != rowSet[col + 1]) {
                     addWall = false; // В конце наоборот убираем стену
                }
            }
            
            if (addWall) {
                grid[2 * row + 1][2 * col + 2] = 1; // Ставим стену справа
            } else {
                // Стены нет -> объединяем множества. Все ячейки 2-го множества получают номер 1-го.
                int oldSet = rowSet[col + 1];
                int newSet = rowSet[col];
                for (int k = 0; k < size; ++k) {
                    if (rowSet[k] == oldSet) rowSet[k] = newSet;
                }
                grid[2 * row + 1][2 * col + 2] = 0; // Ломаем стену
            }
        }

        //Создание нижних границ (проходы вниз)
        if (row < size - 1) { // Для всех, кроме последней строки
            vector<bool> hasDownPath(size, false);

            // Находим уникальные множества в этой строке
            vector<int> uniqueSets = rowSet;
            sort(uniqueSets.begin(), uniqueSets.end());
            uniqueSets.erase(unique(uniqueSets.begin(), uniqueSets.end()), uniqueSets.end());

            // Гарантируем, что у каждого множества есть хотя бы один выход вниз
            for (int setId : uniqueSets) {
                vector<int> indices;
                // Собираем все индексы колонок, принадлежащих этому множеству
                for (int col = 0; col < size; ++col) {
                    if (rowSet[col] == setId) {
                        indices.push_back(col);
                    }
                }

                // Выбираем случайную колонку из этого множества для прохода вниз
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> dist(0, indices.size() - 1);
                hasDownPath[indices[dist(gen)]] = true; 
            }

            // Применяем решения к физической сетке
            for (int col = 0; col < size; ++col) {
                if (hasDownPath[col]) {
                    grid[2 * row + 2][2 * col + 1] = 0; // Пробиваем пол
                } else {
                    grid[2 * row + 2][2 * col + 1] = 1; // Оставляем стену
                    rowSet[col] = 0; // В следующей строке эта ячейка будет без множества
                }
            }
        }
    }

    return maze; // Возвращаем готовый объект
}

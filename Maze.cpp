#include "Maze.h"
//хранит данные (массив 0 и 1)
Maze::Maze(unsigned int size): size(size) {
    //Размер сетки. Потому что между любыми двумя клетками-проходами должна быть стена.
    grid.resize(2 * size + 1, vector<int>(2*size+1, 1));
}

// Установить значение клетки (0 или 1)
void Maze::setCell(int row, int col, int val) {
    if (isValid(row, col)) { //проверяем, существуют ли такие координаты
        grid[row][col] = val;
    }
}

// Получить значение клетки
int Maze::getCell(int row, int col) const {
    if (isValid(row, col)) {
        return grid[row][col];
    }
    return -1; // Возвращаем код ошибки, если координаты неверны
}

unsigned int Maze::getSize() const {
    return size;
}

const vector<vector<int> > &Maze::getGrid() const {
    return grid;
}

// Проверка: координаты внутри массива?
bool Maze::isValid(int row, int col) const {
    return row >= 0 && row < grid.size() &&
        col >= 0 && col < grid[0].size();
}

// Проверка на стену
bool Maze::isWall(int row, int col) const {
    return isValid(row, col) && grid[row][col] == 1; // 1 - это код стены
}

// Проверка на проход
bool Maze::isPath(int row, int col) const {
    return isValid(row, col) && grid[row][col] == 0; // 0 - это код прохода
}

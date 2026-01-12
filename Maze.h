#pragma once

#include <vector>
using namespace std;

class Maze {
    // Двумерный массив для хранения состояния клеток.
    // 1 - стена, 0 - проход.
    vector<vector<int>> grid;
    unsigned int size; // Логический размер лабиринта (количество проходов)

public:
    Maze(unsigned int s); // Конструктор
    virtual ~Maze() = default; // Деструктор по умолчанию

    // Методы доступа (геттеры и сеттеры)
    void setCell(int row, int col, int val);
    int getCell(int row, int col) const;
    unsigned int getSize() const;
    const vector<vector<int>>& getGrid() const; // Возвращает ссылку на сетку (для чтения)

    // Проверки границ и типов клеток
    bool isValid(int row, int col) const;// Не вышли ли координаты за пределы массива
    bool isPath(int row, int col) const;// Является ли клетка проходом
    bool isWall(int row, int col) const;//Является ли клетка стеной
};
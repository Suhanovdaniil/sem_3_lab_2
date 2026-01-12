#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Maze.h"
using namespace std;

class MazeRender {
    Maze* maze; // Указатель на данные лабиринта
    unsigned int windowSize;
    vector<vector<sf::RectangleShape>> visualGrid; // Массив квадратов для рисования
    bool ownsMaze; // Флаг: владеет ли этот класс памятью Maze (надо ли удалять)

public:
    MazeRender(Maze* maze, unsigned int window, bool ownership = false);
    ~MazeRender();

    void updateMaze(Maze* newMaze, bool ownership = false); // Обновить лабиринт
    void render(sf::RenderWindow& window); // Нарисовать в окне
    void setColor(int row, int col, sf::Color color); // Покрасить клетку
    void resetColors(); // Сбросить цвета (кроме стен)

    pair<int, int> getCell(int pixelX, int pixelY) const;//Конвертация пикселей в координаты
    Maze* getMaze() const;

private:
    void clearMaze();//Очистка памяти
    void initGrid();//Создание квадратиков
};

#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.h"
#include "Maze.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "MazeRender.h"

using namespace std;

// Паттерн "Фасад"
class InputHandler;

// Класс Game предоставляет простой интерфейс для управления всей системой.
class Game {
    sf::RenderWindow window; // Окно приложения
    unsigned int mazeSize;
    unsigned int windowSize;

    // Компоненты системы
    Maze* maze;
    MazeGenerator* mazeGenerator;
    MazeSolver* mazeSolver;
    MazeRender* mazeRenderer;
    InputHandler* inputHandler;

    // Логика выбора точек
    std::pair<int, int> startPoint;
    std::pair<int, int> endPoint;
    bool startSet;
    bool endSet;

public:
    Game(unsigned int gridSize, unsigned int windowSize);
    ~Game(); // Деструктор обязателен для очистки памяти

    void run(); // Главный цикл
    
    // Методы игровой логики
    void regenerateMaze();
    void solveMaze();
    void clearSolution();

    // Работа с точками
    void setStartPoint(int row, int col);
    void setEndPoint(int row, int col);
    void clearPoints();

    std::pair<int, int> getCellFromPixel(int pixelX, int pixelY) const;

    // Обработчики команд (вызываются из InputHandler)
    void handleRegenerateCommand();
    void handleSolveCommand();
    void handleClearCommand();
    void handleMouseClick(int pixelX, int pixelY, bool isLeftButton);

private:
    void initialize();// Выделение ресурсов
    void cleanup();// Освобождение ресурсов
    void processEvents();// Обработка очереди событий
    void update();// Обновление состояния
    void render();// Отрисовка кадра
};
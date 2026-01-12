#include "MazeRender.h"

// Конструктор: инициализирует переменные и создает сетку квадратиков
MazeRender::MazeRender(Maze* maze, unsigned int window, bool ownership) :
    maze(maze), windowSize(window), ownsMaze(ownership) {
    initGrid();
}

MazeRender::~MazeRender() {
    clearMaze();
}

// Удаление лабиринта, если мы им владеем
void MazeRender::clearMaze() {
    if (ownsMaze && maze) {
        delete maze;
        maze = nullptr;
    }
}

// Инициализация графической сетки
void MazeRender::initGrid() {
    int mazeSize = maze->getGrid().size();
    // Вычисляем размер одной клетки в пикселях
    float cellSize = static_cast<float>(windowSize) / mazeSize;
    
    visualGrid.resize(mazeSize, vector<sf::RectangleShape>(mazeSize));
    
    for (int i = 0; i < mazeSize; ++i) {
        for (int j = 0; j < mazeSize; ++j) {
            // Создаем квадрат нужного размера
            visualGrid[i][j] = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
            visualGrid[i][j].setPosition(j * cellSize, i * cellSize);
            
            // Если стена - черный, проход - белый
            if (maze->isWall(i, j)) {
                visualGrid[i][j].setFillColor(sf::Color::Black);
            } else {
                visualGrid[i][j].setFillColor(sf::Color::White);
            }
        }
    }
}

// Обновление лабиринта (например, при регенерации)
void MazeRender::updateMaze(Maze *newMaze, bool ownership) {
    clearMaze(); // Удаляем старый
    maze = newMaze;
    ownsMaze = ownership;
    resetColors(); // Сбрасываем цвета

    // Пересоздаем сетку, так как размер мог измениться (или просто для надежности)
    initGrid(); 
}

// Главный метод отрисовки
void MazeRender::render(sf::RenderWindow &window) {
    for (const auto& row : visualGrid) {
        for (const auto& cell : row) {
            window.draw(cell); // Рисуем каждый квадрат
        }
    }
}

// Покрасить конкретную клетку (например, в зеленый для пути)
void MazeRender::setColor(int row, int col, sf::Color color) {
    if (row >= 0 && row < visualGrid.size() &&
        col >= 0 && col < visualGrid.size()) {
        visualGrid[row][col].setFillColor(color);
    }
}

// Сброс цветов (возврат к черно-белому)
void MazeRender::resetColors() {
    if (!maze) return;
    int mazeSize = visualGrid.size();
    for (int i = 0; i < mazeSize; ++i) {
        for (int j = 0; j < mazeSize; ++j) {
            if (maze->isWall(i, j)) {
                visualGrid[i][j].setFillColor(sf::Color::Black);
            } else {
                visualGrid[i][j].setFillColor(sf::Color::White);
            }
        }
    }
}

// Перевод координат мыши (пиксели) в координаты клетки (строка, столбец)
pair<int, int> MazeRender::getCell(int pixelX, int pixelY) const {
    if (!maze) return {-1, -1};
    int mazeSize = maze->getGrid().size();
    float cellSize = static_cast<float>(windowSize) / mazeSize;

    // Простое деление координаты на размер клетки
    int col = static_cast<int>(pixelX / cellSize);
    int row = static_cast<int>(pixelY / cellSize);

    if (maze->isValid(row, col)) {
        return {row, col};
    }
    return {-1, -1};
}

Maze* MazeRender::getMaze() const {
    return maze;
}

#include "Game.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "InputHandler.h"
#include <iostream>

// Конструктор: инициализирует окно и переменные
Game::Game(unsigned int mazeSize, unsigned int windowSize) 
    : mazeSize(mazeSize), windowSize(windowSize),
      window(sf::VideoMode(windowSize, windowSize), "Лабиринт"),
      maze(nullptr), mazeGenerator(nullptr), mazeSolver(nullptr),
      mazeRenderer(nullptr), inputHandler(nullptr),
      startSet(false), endSet(false),
      startPoint({-1, -1}), endPoint({-1, -1}) {
    
    // Проверка корректности ввода
    if (mazeSize == 0 || windowSize == 0) {
        throw std::invalid_argument("Указаны некорректные значения. Повторите ввод");
    }
    
    initialize(); // Запуск создания объектов
}

Game::~Game() {
    cleanup(); // Обязательно чистим память при удалении игры
}

// Освобождение памяти (delete для всех указателей)
void Game::cleanup() {
    delete inputHandler;
    delete mazeRenderer;
    delete mazeSolver;
    delete mazeGenerator;
    delete maze;
}

// Создание компонентов (Фабрики, Стратегии)
void Game::initialize() {
    mazeGenerator = new EllerMazeGenerator(); // Используем алгоритм Эллера
    mazeSolver = new BFSSolver();// Используем BFS
    
    regenerateMaze(); // Генерируем первый лабиринт
    
    inputHandler = new InputHandler(this); // Создаем обработчик ввода
}

// Главный цикл (Game Loop)
void Game::run() {
    while (window.isOpen()) {
        processEvents();// 1. Ввод
        // update();// 2. Логика (сейчас пустая)
        render();// 3. Отрисовка
    }
}

// Обработка событий окна
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close(); // Нажали крестик
        } else {
            // Передаем остальные события посреднику
            inputHandler->handleEvent(event);
        }
    }
}

// Отрисовка
void Game::render() {
    window.clear(); // Очистка черным
    if (mazeRenderer) {
        mazeRenderer->render(window); // Рисуем лабиринт
    }
    window.display(); // Показываем кадр
}

// Регенерация лабиринта
void Game::regenerateMaze() {
    if (maze) delete maze; // Удаляем старый
    
    maze = mazeGenerator->generate(mazeSize); // Создаем новый через генератор
    
    // Обновляем рендерер
    if (mazeRenderer) {
        mazeRenderer->updateMaze(maze);
    } else {
        mazeRenderer = new MazeRender(maze, windowSize);
    }
    
    clearPoints(); // Сбрасываем старт и финиш
}

// Запуск поиска пути
void Game::solveMaze() {
    clearSolution(); // Стираем старый путь
    if (startSet && endSet) {
        // Вызываем солвер (стратегию)
        auto path = mazeSolver->solve(maze, startPoint, endPoint);
        
        // Красим найденный путь
        for (const auto& cell : path) {
            if (cell != startPoint && cell != endPoint) {
                mazeRenderer->setColor(cell.first, cell.second, sf::Color::Green);
            }
        }
    }
}

// Очистка только пути (цветов), оставляя старт и финиш
void Game::clearSolution() {
    if (mazeRenderer) {
        mazeRenderer->resetColors();
        // Восстанавливаем цвета старта и финиша, так как resetColors все сбросил
        if (startSet) mazeRenderer->setColor(startPoint.first, startPoint.second, sf::Color::Red);
        if (endSet) mazeRenderer->setColor(endPoint.first, endPoint.second, sf::Color::Blue);
    }
}

// Установка точки старта (Красная)
void Game::setStartPoint(int row, int col) {
    if (maze && mazeRenderer && maze->isPath(row, col)) { // Только на проходе
        if (startSet) {
            mazeRenderer->setColor(startPoint.first, startPoint.second, sf::Color::White); // Стираем старую
        }
        startPoint = {row, col};
        startSet = true;
        mazeRenderer->setColor(row, col, sf::Color::Red);
        clearSolution(); // Если сдвинули точку, старый путь неактуален
    }
}

// Установка точки финиша (Синяя)
void Game::setEndPoint(int row, int col) {
    if (maze && mazeRenderer && maze->isPath(row, col)) {
        if (endSet) {
            mazeRenderer->setColor(endPoint.first, endPoint.second, sf::Color::White);
        }
        endPoint = {row, col};
        endSet = true;
        mazeRenderer->setColor(row, col, sf::Color::Blue);
        clearSolution();
    }
}

void Game::clearPoints() {
    if (mazeRenderer) {
        mazeRenderer->resetColors();
    }
    startSet = false;
    endSet = false;
    startPoint = {-1, -1};
    endPoint = {-1, -1};
}

std::pair<int, int> Game::getCellFromPixel(int pixelX, int pixelY) const {
    if (mazeRenderer) {
        return mazeRenderer->getCell(pixelX, pixelY);
    }
    return {-1, -1};
}

// Методы-обработчики (вызываются из InputHandler)
void Game::handleRegenerateCommand() { regenerateMaze(); }
void Game::handleSolveCommand() { solveMaze(); }
void Game::handleClearCommand() { clearPoints(); clearSolution(); }

void Game::handleMouseClick(int pixelX, int pixelY, bool isLeftButton) {
    auto [row, col] = getCellFromPixel(pixelX, pixelY);
    if (row != -1) {
        if (isLeftButton) {
            setStartPoint(row, col);
        } else {
            setEndPoint(row, col);
        }
    }
}

void Game::update() {
    //логика реального времени не нужна для пошагового лабиринта
}

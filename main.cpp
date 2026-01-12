#include "Game.h"
#include <iostream>

using namespace std;

// Функция для получения ввода от пользователя
unsigned int getInput(const string& prompt) {
    unsigned int value;
    cout << prompt;
    cin >> value;
    return value;
}

int main() {
    //Спрашиваем настройки у пользователя
    unsigned int windowSize = getInput("Введите размер окна (например, 800): ");
    unsigned int gridSize = getInput("Введите количество клеток лабиринта (например, 20): ");

    try {
        //Создаем объект игры (Паттерн Фасад).
        // Конструктор Game инициализирует все подсистемы (генератор, рендер и т.д.)
        Game game(gridSize, windowSize);
        //Запускаем главный цикл игры
        game.run();
        
    } catch (const exception& e) {
        // Ловим ошибки (например, если память не выделилась или размеры некорректны)
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

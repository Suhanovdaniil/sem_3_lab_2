#pragma once

#include "Maze.h"
using namespace std;

// Паттерн или Стратегия создания(переопределить в произвольном калссе сохранив при это её сигнатуру)
// Позволяет подменять алгоритмы генерации без изменения остального кода.

class MazeGenerator {
public:
    virtual ~MazeGenerator() = default;
    virtual Maze* generate(unsigned int size) = 0;
};

// Конкретная реализация: Алгоритм Эллера (реализовать динамическое свзявание фий ао время выполнения программы)
class EllerMazeGenerator : public MazeGenerator {
    bool randomBool(); // Вспомогательная функция

public:
    Maze* generate(unsigned int size) override;
};

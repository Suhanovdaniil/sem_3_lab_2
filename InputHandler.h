#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
class Game;

using namespace std;

// Паттерн "Посредник"
// Этот класс принимает сырые события SFML и преобразует их в команды для Game.
class InputHandler {
    Game* game_; // Ссылка на управляющий класс игры

public:
    InputHandler(Game* game) : game_(game) {}
    void handleEvent(const sf::Event& event); // Метод распределения событий

private:
    void handleKeyPress(sf::Keyboard::Key key); // Нажатия клавиш
    void handleMouseClick(const sf::Event::MouseButtonEvent& mouse); // Клики мыши
};
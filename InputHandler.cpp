#include "InputHandler.h"
#include "Game.h"

void InputHandler::handleEvent(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            handleKeyPress(event.key.code);
            break;

        case sf::Event::MouseButtonPressed:
            handleMouseClick(event.mouseButton);
            break;

        default:
            break;
    }
}

void InputHandler::handleKeyPress(sf::Keyboard::Key key) {
    // R - перегенерировать, S - решить, C - очистить путь
    switch (key) {
        case sf::Keyboard::R:
            game_->handleRegenerateCommand();
        break;

        case sf::Keyboard::S:
            game_->handleSolveCommand();
        break;

        case sf::Keyboard::C:
            game_->handleClearCommand();
        break;

        default:
            break;
    }
}

void InputHandler::handleMouseClick(const sf::Event::MouseButtonEvent &mouse) {
    bool isLeftButton = (mouse.button == sf::Mouse::Left);
    // Передаем координаты мыши и тип кнопки в игру
    game_->handleMouseClick(mouse.x, mouse.y, isLeftButton);
}

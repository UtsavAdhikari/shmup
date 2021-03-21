#pragma once

#include "Game.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MainWindow
{
public:
    explicit MainWindow();
    virtual ~MainWindow() = default;

    void start();

private:
    sf::RenderWindow m_window;
    Game m_game;
};
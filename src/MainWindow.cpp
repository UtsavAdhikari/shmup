#include "MainWindow.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdio>

namespace
{
    const auto style = sf::Style::Titlebar
                     | sf::Style::Close;
                    // | sf::Style::Resize // TODO

    constexpr int height = 1400;
    constexpr int width = 1000;
    const std::string title = "SHMUP"; // TODO: title
}


MainWindow::MainWindow()
    : m_window(sf::VideoMode(width, height), title, style)
    , m_game(m_window)
{
    m_window.setPosition({ 1920 - width, 1080 - height });
}

void MainWindow::start()
{
    try
    {
        m_game.run();
    }
    catch (std::exception& e) 
    {
        printf("*** %s\n", e.what());
    }
}

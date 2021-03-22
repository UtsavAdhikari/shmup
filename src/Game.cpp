#include "Game.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <string>


Game::Game(sf::RenderWindow& window)
    : m_window(window)
    , m_paused(false)
    , m_world(window)
    // FIXME: Profling shit
    , m_statsFont()
    , m_statsText()
    , m_statsUpdateTime()
    , m_statsFPS(0)
{
    printf("%s\n", __PRETTY_FUNCTION__);

    // FIXME: Profiling shit
    // TODO: Resource paths
    m_statsFont.loadFromFile("../../resources/fonts/saxmono.ttf");
    m_statsText.setFont(m_statsFont);
    m_statsText.setPosition(10.f, 10.f);
    m_statsText.setCharacterSize(50);
}

void Game::run()
{
    printf("%s\n", __PRETTY_FUNCTION__);
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    sf::Event event;
    sf::Clock clock;
    sf::Time lastUpdate = sf::Time::Zero;

    while(m_window.isOpen())
    {
        processEvents();
        // Use fixed time steps for game engine processing
        lastUpdate += clock.restart();
        while(lastUpdate > TIME_PER_FRAME)
        {
            lastUpdate -= TIME_PER_FRAME;
            processEvents();

            if (! m_paused)
                update(TIME_PER_FRAME);
        }
        updateStatistics(lastUpdate);

        render();
    }
}

void Game::update(sf::Time delta)
{
    m_world.update(delta);
}

void Game::updateStatistics(sf::Time delta)
{
    m_statsUpdateTime += delta;
    m_statsFPS += 1;
    if(m_statsUpdateTime >= sf::seconds(1))
    {
        m_statsText.setString(
            "FPS:   " + std::to_string(m_statsFPS) + "\n" +
            "Delta: " + std::to_string(m_statsUpdateTime.asMicroseconds() / m_statsFPS) + "us");
        
        m_statsUpdateTime -= sf::seconds(1);
        m_statsFPS = 0;
    }
}

void Game::render()
{
    m_window.clear(sf::Color::Black);

    m_world.draw();

    // FIXME: profling shit
    m_window.draw(m_statsText);

    m_window.display();
}

void Game::processEvents()
{
    // Handle window events
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        handleEvent(event);
    }

}

void Game::handleEvent(sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::KeyPressed:
            // TODO
            // handleKeyPress(event.key);
            break;
        
        case sf::Event::GainedFocus:
            printf("Focus Gained - resuming game updates\n");
            m_paused = false;
            break;

        case sf::Event::LostFocus:
            printf("Focus Lost - pausing game updates\n");
            m_paused = true;
            break;

        default:
            break;
    }

}
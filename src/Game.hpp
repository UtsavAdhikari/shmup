#pragma once

#include "World.hpp"
#include "ResourceBank.hpp"
#include "Textures.hpp"

#include <SFML/Graphics.hpp>
#include <cstddef>

class Game
{
public:
    explicit Game(sf::RenderWindow& window);
    virtual ~Game() = default;

    void run();

private:
    void update(sf::Time delta);
    void updateStatistics(sf::Time delta);
    void render();
    void processEvents();
    void handleEvent(sf::Event& event);

    sf::RenderWindow& m_window;

    ResourceBank<sf::Texture, Texture::ID> m_textures;

    World m_world;

    bool m_paused;

    // profiling shit
    sf::Font m_statsFont;
    sf::Text m_statsText;
    sf::Time m_statsUpdateTime;
    // NOTE: not atomic, really just a frame counter that is queried each second
    std::size_t m_statsFPS;
};
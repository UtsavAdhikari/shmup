#pragma once

#include "World.hpp"
#include "ResourceBank.hpp"
#include "Textures.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    explicit Game(sf::RenderWindow& window);
    virtual ~Game() = default;

    void run();

private:
    void update(sf::Time delta);
    void render();
    void processEvents();
    void handleEvent(sf::Event& event);

    sf::RenderWindow& m_window;

    ResourceBank<sf::Texture, Texture::ID> m_textures;

    World m_world;

    bool m_paused;
};
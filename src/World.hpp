#pragma once

#include "CommandQueue.hpp"
#include "PlayerAircraft.hpp"
#include "SceneNode.hpp"
#include "ResourceBank.hpp"
#include "Textures.hpp"

#include <SFML/Graphics.hpp>

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window);
    
    void update(sf::Time delta);
    void draw();

    CommandQueue& getCommandQueue();
private:
    void loadTextures();
    void buildScene();

    enum Layer
    {
        Background,
        Foreground,
        //
        Count
    };

    sf::RenderWindow& m_window;
    sf::View m_view;
    ResourceBank<sf::Texture, Texture::ID> m_textures;

    SceneNode m_sceneGraph;
    std::array<SceneNode*, Layer::Count> m_sceneLayers;

    sf::FloatRect m_worldBounds;
    float m_scrollSpeed;

    sf::Vector2f m_spawnPosition;
    PlayerAircraft* m_playerAircraft;

    CommandQueue m_commandQueue;
};
#include "World.hpp"
#include "CommandQueue.hpp"
#include "PlayerAircraft.hpp"
#include "Textures.hpp"
#include "SpriteNode.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>


World::World(sf::RenderWindow& window)
    : m_window(window)
    , m_view(window.getDefaultView())
    , m_worldBounds(
        0.f,0.f,
        m_view.getSize().x,
        4000.f)
    , m_spawnPosition(m_view.getSize().x / 2.f,
                      m_worldBounds.height - 100)
    , m_playerAircraft(nullptr)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    loadTextures();
    buildScene();

    m_view.setCenter(m_view.getSize().x / 2.f, m_worldBounds.height - (m_view.getSize().y / 2.0f));

    // FIXME:
    m_scrollSpeed = 000;

}

void World::update(sf::Time delta)
{
    // printf("%s\n", __PRETTY_FUNCTION__);
    // Scroll the view upwards
    m_view.move({ 0.f, -m_scrollSpeed * delta.asSeconds() });

    // HACk: Camera movement hack
    const int hackSpeed = 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_view.move({ 0.f, -hackSpeed * delta.asSeconds() });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_view.move({ 0.f, hackSpeed * delta.asSeconds() });

    //TODO bring player with us
    
    // Forward commands to scene graph
    while (! m_commandQueue.isEmpty())
    {
        m_sceneGraph.onCommand(m_commandQueue.pop(), delta);
    }

    m_sceneGraph.update(delta);
}

void World::draw()
{
    m_window.setView(m_view);
    m_window.draw(m_sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return m_commandQueue;
}

void World::loadTextures()
{
    printf("%s\n", __PRETTY_FUNCTION__);
    m_textures.load(Texture::ID::PlayerAircraft, "../../resources/images/sprite.png");
    m_textures.load(Texture::ID::Grid200, "../../resources/images/grid200.png");
    m_textures.load(Texture::ID::Grid100, "../../resources/images/grid100.png");
}

void World::buildScene()
{
    printf("%s\n", __PRETTY_FUNCTION__);

    // Create scene layers
    for(unsigned int i = 0; i < Layer::Count; ++i)
    {
        auto layer = std::make_shared<SceneNode>();
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(layer);
    }

    // Build background
    sf::Texture& bgTexture = m_textures.get(Texture::ID::Grid100);
    sf::IntRect bgTextureRect(m_worldBounds);
    bgTexture.setRepeated(true);

    auto bgSprite = std::make_unique<SpriteNode>(bgTexture, bgTextureRect);
    bgSprite->setPosition(m_worldBounds.left, m_worldBounds.top);

    m_sceneLayers[Layer::Background]->attachChild(std::move(bgSprite));


    // Add player aircraft
    auto playerAircraft = std::make_unique<PlayerAircraft>(m_textures);
    m_playerAircraft = playerAircraft.get();
    m_playerAircraft->setPosition(m_spawnPosition);
    // TODO: set velocity to scroll velociy;
    printf("Attaching player\n");
    m_sceneLayers[Layer::Foreground]->attachChild(std::move(playerAircraft));

}
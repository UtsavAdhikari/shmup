#pragma once

#include "SceneNode.hpp"

#include <SFML/Graphics.hpp>

class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    explicit SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite m_sprite;
};
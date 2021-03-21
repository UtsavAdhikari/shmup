#pragma once

#include "Command.hpp"
#include "Entity.hpp"
#include "ResourceBank.hpp"
#include "Textures.hpp"

#include <SFML/Graphics.hpp>

class PlayerAircraft : public Entity
{
public:
    explicit PlayerAircraft(const ResourceBank<sf::Texture, Texture::ID>& textures);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    Category getCategory() const override;

private:

    sf::Sprite m_sprite;
};
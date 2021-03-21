#include "PlayerAircraft.hpp"
#include "Command.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstdio>

PlayerAircraft::PlayerAircraft(const ResourceBank<sf::Texture, Texture::ID>& textures)
    : m_sprite(textures.get(Texture::ID::PlayerAircraft))
{
    printf("%s\n", __PRETTY_FUNCTION__);
    // Center the origin
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void PlayerAircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

Category PlayerAircraft::getCategory() const
{
    return Category::Player;
}
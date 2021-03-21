#pragma once

#include "SceneNode.hpp"

#include <SFML/System.hpp>

class Entity : public SceneNode
{
public:
    Entity() = default;
    virtual ~Entity() = default;


    void setVelocity(sf::Vector2f velocity);

    sf::Vector2f getVelocity() const;

    void updateCurrent(sf::Time delta);
    
private:
    sf::Vector2f m_velocity;
};

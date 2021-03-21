#include "SceneNode.hpp"
#include "Command.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <stdexcept>

void SceneNode::onCommand(const Command &command, sf::Time delta)
{
    if (command.category & static_cast<unsigned int>(getCategory()))
    {
        command.action(*this, delta);
    }

    for (auto& child : m_children)
    {
        child->onCommand(command, delta);
    }
}

void SceneNode::attachChild(std::shared_ptr<SceneNode> child)
{
    if (! child)
        printf("Child is null\n");

    child->m_parent = this;
    m_children.push_back(std::move(child));
}

void SceneNode::update(sf::Time delta)
{
    updateCurrent(delta);
    updateChildren(delta);
}

std::shared_ptr<SceneNode> SceneNode::detachChild(const SceneNode &node)
{
    const auto found = std::find_if(m_children.begin(), m_children.end(), 
        [&node](std::shared_ptr<SceneNode> n) -> bool
        {
           return n.get() == &node;
        });
    
    if (found == m_children.end())
    {
        // TODO, do better, or not throw
        throw std::runtime_error("Child not found\n");
    }

    std::shared_ptr<SceneNode> detached = std::move(*found);
    detached->m_parent = nullptr;
    m_children.erase(found);

    return detached;
}

Category SceneNode::getCategory() const
{
    return Category::Scene;
}

sf::Transform SceneNode::getWorldTransform()
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
    {
        transform *= node->getTransform(); 
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition()
{
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Empty
}

void SceneNode::updateCurrent(sf::Time delta)
{
    // Empty
}

void SceneNode::updateChildren(sf::Time delta)
{
    for(auto& child : m_children)
    {
        child->update(delta);
    }
}


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);

    for (auto& child : m_children)
    {
        child->draw(target, states);
    }
}

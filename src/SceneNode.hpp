#pragma once

#include "Command.hpp"

#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>

class SceneNode
    : public sf::Drawable
    , public sf::Transformable
    , private sf::NonCopyable
{
public:
    SceneNode() = default;
    virtual ~SceneNode() = default;

    virtual void onCommand(const Command& command, sf::Time delta);

    virtual Category getCategory() const;

    void attachChild(std::shared_ptr<SceneNode> child);
    void update(sf::Time delta);

    std::shared_ptr<SceneNode> detachChild(const SceneNode& node);

    sf::Transform getWorldTransform();

    sf::Vector2f getWorldPosition();

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time delta);
    virtual void updateChildren(sf::Time delta);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

    std::vector<std::shared_ptr<SceneNode>> m_children;
    SceneNode* m_parent;
};
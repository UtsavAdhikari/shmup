#pragma once

#include <SFML/System/Time.hpp>

#include <functional>

class SceneNode;

enum class Category : unsigned int
{
    None        = 0,
    Scene       = 1 << 0, 
    Player      = 1 << 1, 
};

struct Command
{
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category;
};
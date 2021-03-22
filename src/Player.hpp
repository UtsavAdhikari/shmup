#pragma once

#include "CommandQueue.hpp"
#include <SFML/Window/Event.hpp>
class Player
{
public:
    // TODO: pass q as ctor param?

    void handleEvent(sf::Event& event, CommandQueue& commands);

};
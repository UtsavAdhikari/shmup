#pragma once

#include "Command.hpp"

#include <queue>

class CommandQueue
{
public:
    // TODO need copy?
    void push(const Command command);
    Command pop();
    bool isEmpty();

private:
    std::queue<Command> m_queue;
};
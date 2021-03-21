#include "CommandQueue.hpp"

void CommandQueue::push(const Command command)
{
    // TODO minimise copies
    m_queue.push(command);
}

Command CommandQueue::pop()
{
    const auto command = m_queue.front();
    m_queue.pop();

    return command;
}

bool CommandQueue::isEmpty()
{
    return m_queue.empty();
}
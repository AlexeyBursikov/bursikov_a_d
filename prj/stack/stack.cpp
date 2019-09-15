#include "stack.h"
#include <stdexcept> 

Stack::Stack(): size_(0)
{
}

bool Stack::isEmpty()
{
    return data_.empty();
}

void Stack::push(int x)
{
    data_.push_back(x);
}

void Stack::pop()
{
    if (!data_.empty())
        data_.pop_back();
}

int Stack::top()
{
    if (isEmpty())
    {
        throw std::out_of_range("retrieving item from empty stack");
    }
    else
    {
        return data_.back();
    }
}
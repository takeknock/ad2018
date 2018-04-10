#include "Stack.h"

Stack::Stack(const std::size_t max)
:_maxSize(max), index(0)
{
    _container = new int[_maxSize*sizeof(int)];
}

void Stack::push(int data)
{
    if (isFull())
    {
        throw new exception;
    }
    _container[index] = data;
    index++;
}

int Stack::pop()
{
    return 0;
}

bool Stack::isEmpty()
{
    return true;
}

bool Stack::isFull()
{
    return true;
}
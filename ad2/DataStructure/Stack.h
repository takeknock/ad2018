#pragma once
#include <memory>

#include "macroh.h"

class Stack {
public:
    DS_API Stack(const std::size_t maxSize);
    DS_API void push(int data);
    DS_API int pop();
    DS_API bool isFull();
    DS_API bool isEmpty();

private:
    const std::size_t _maxSize;
    std::size_t index;
    int*_container;
};
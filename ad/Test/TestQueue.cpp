#include <cassert>

#include "TestQueue.h"

#include "DataStructure/Queue.h"

void TestQueue::runTest()
{
    testDequeue();
    testIsEmpty();
    testIsFull();
}

void TestQueue::testDequeue()
{
    ds::Queue<int> queue = ds::Queue<int>(2);
    queue.enqueue(1);
    queue.enqueue(2);
    int out = queue.dequeue();
    int expected = 1;
    assert(expected == out);
}

void TestQueue::testIsEmpty()
{
    ds::Queue<int> queue = ds::Queue<int>(2);
    assert(queue.isEmpty());
    queue.enqueue(1);
    assert(!queue.isEmpty());
}

void TestQueue::testIsFull()
{
    ds::Queue<int> queue = ds::Queue<int>(2);
    assert(!queue.isFull());
    queue.enqueue(1);
    queue.enqueue(1);
    assert(queue.isFull());
}
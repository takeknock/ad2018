#include <cassert>
#include <stack>
#include "TestStack.h"

#include "DataStructure/Stack.h"


void TestStack::runTest() {
    testPush();
    testPop();
    testIsEmpty();
    testIsFull();
    testValueType();
}


void TestStack::testPush() {
    ds::Stack<double> stack = ds::Stack<double>(5);
    stack.push(1);
}

void TestStack::testPop() {
    int expected = 100;
    ds::Stack<int> stack = ds::Stack<int>(5);
    stack.push(100);
    int actual = stack.pop();
    assert(expected == actual);
}

void TestStack::testIsEmpty() {
    ds::Stack<double> stack = ds::Stack<double>(5);
    assert(stack.isEmpty());
    stack.push(1.0);
    assert(!stack.isEmpty());
}

void TestStack::testIsFull() {
    ds::Stack<int> stack = ds::Stack<int>(5);
    stack.push(1);  
    stack.push(1);
    stack.push(1);
    stack.push(1);
    assert(!stack.isFull());
    stack.push(1);
    assert(stack.isFull());
}

void TestStack::testValueType() {
    bool check = std::is_same<ds::Stack<double>::value_type, double>::value;
    assert(check);
}
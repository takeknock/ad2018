#include "TestStack.h"
#include "TestQueue.h"

int main() {
    TestStack ts = TestStack();
    ts.runTest();


    TestQueue tq = TestQueue();
    tq.runTest();
    return 0;
}
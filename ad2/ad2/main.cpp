#include <iostream>
#include "ad/dual_number.h"
#include "DataStructure/Stack.h"


int main() {
    //ad::dual_number<3> spot = ad::dual_number<3>(0);
    //ad::dual_number<3> volatility = ad::dual_number<3>(1);

    Stack stack = Stack(2);
    stack.isEmpty();
    std::cout << stack.isEmpty() << std::endl;

    system("pause");
    return 0;
}
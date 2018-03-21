#include <iostream>
#include "ad/dual.h"

int main(){
    const double x = 1.0;
    ad::dual xv = ad::dual(x, 1.0);
    const double a = 2.0;
    ad::dual av = ad::dual(a);

    ad::dual y = av * xv + av + xv;
    std::cout << y.getValue() << std::endl;
    std::cout << y.getDerivative() << std::endl;

    int xxx = 0;
    std::cin >> xxx;

    return 0;
}
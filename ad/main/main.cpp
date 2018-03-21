#include <iostream>
#include <cassert>
#include "math/math.h"
#include "ad/dual.h"

double black(
    const double interestRate, 
    const double volatility, 
    const double maturity, 
    const double spot, 
    const double strike)
{
    assert(volatility > std::numeric_limits<double>::epsilon());
    const double root_t = std::sqrt(maturity);
    const double d1 = (std::log(spot / strike) + (interestRate + 0.5 * volatility * volatility) * maturity) 
        / (volatility * std::sqrt(maturity));
    const double d2 = d1 - volatility * std::sqrt(maturity);
    math::distribution::StandardNormal d = math::distribution::StandardNormal();
    const double discountFactor = std::exp(-interestRate * maturity);;
    return spot * d.cdf(d1) - strike * discountFactor * d.cdf(d2);
}

int main(){
    const double x = 1.0;
    ad::dual xv = ad::dual(x, 1.0);
    const double a = 2.0;
    ad::dual av = ad::dual(a);

    ad::dual y = av * xv + av + xv;
    std::cout << y.getValue() << std::endl;
    std::cout << y.getDerivative() << std::endl;

    const double interestRate = 0.01;
    const double volatility = 0.01;
    const double maturity = 1.0;
    const double spot = 110.0;
    const double strike = 100.0;


    const double pv = black(interestRate, volatility, maturity, spot, strike);
    std::cout << pv << std::endl;
    int xxx = 0;
    std::cin >> xxx;

    return 0;
}
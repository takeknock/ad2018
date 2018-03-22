#include <iostream>
#include <cassert>
#include "math/distribution.h"
#include "ad/DualNumber.h"
#include "math/functions.h"

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
    const double discountFactor = std::exp(-interestRate * maturity);
    return spot * d.cdf(d1) - strike * discountFactor * d.cdf(d2);
}

ad::DualNumber blackV(
    ad::DualNumber& interestRate,
    ad::DualNumber& volatility,
    ad::DualNumber& maturity,
    ad::DualNumber& spot,
    ad::DualNumber& strike)
{
    assert(volatility.getValue() > std::numeric_limits<double>::epsilon());
    ad::DualNumber root_t = math::sqrt(maturity);
    ad::DualNumber d1 = (math::log(spot / strike) + (interestRate + ad::DualNumber(0.5) * volatility * volatility) * maturity)
        / (volatility * math::sqrt(maturity));
    ad::DualNumber d2 = d1 - volatility * math::sqrt(maturity);
    math::distribution::StandardNormal d = math::distribution::StandardNormal();
    ad::DualNumber discountFactor = math::exp(ad::DualNumber(-1.0) * interestRate * maturity);
    return spot * d.cdf(d1) - strike * discountFactor * d.cdf(d2);
}

double blackDelta(
    const double interestRate,
    const double volatility,
    const double maturity,
    const double spot,
    const double strike)
{
    const double d1 = (std::log(spot / strike) + (interestRate + 0.5 * volatility * volatility) * maturity)
        / (volatility * std::sqrt(maturity));
    math::distribution::StandardNormal d = math::distribution::StandardNormal();
    return d.cdf(d1);
}

int main(){
    const double x = 3.0;
    ad::DualNumber xv = ad::DualNumber(x, 1.0);
    const double a = 2.0;
    ad::DualNumber av = ad::DualNumber(a);

    ad::DualNumber y = xv / xv;
    std::cout << y.getValue() << std::endl;
    std::cout << y.getDerivative() << std::endl;

    const double interestRate = 0.01;
    const double volatility = 0.1;
    const double maturity = 10.0;
    const double spot = 110.0;
    const double strike = 100.0;

    ad::DualNumber spotV = ad::DualNumber(spot, 1.0);
    ad::DualNumber interestRateV = ad::DualNumber(interestRate);
    ad::DualNumber volatilityV = ad::DualNumber(volatility);
    ad::DualNumber maturityV = ad::DualNumber(maturity);
    ad::DualNumber strikeV = ad::DualNumber(strike);

    const double expected = black(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected PV: " << expected << std::endl;

    ad::DualNumber pv = blackV(interestRateV, volatilityV, maturityV, spotV, strikeV);
    std::cout << "Actual PV: " << pv.getValue() << std::endl;

    const double expectedDelta = blackDelta(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected Delta: " << expectedDelta << std::endl;

    std::cout << "Actual Delta: " << pv.getDerivative() << std::endl;
    int xxx = 0;
    std::cin >> xxx;

    return 0;
}
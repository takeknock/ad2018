#include <iostream>
#include <cassert>
#include "math/distribution.h"

#include "ad/DualNumber.h"
#include "ad/dual_number.h"
#include "ad/functions.h"


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

ad::DualNumber black(
    ad::DualNumber& interestRate,
    ad::DualNumber& volatility,
    ad::DualNumber& maturity,
    ad::DualNumber& spot,
    ad::DualNumber& strike)
{
    assert(volatility.getValue() > std::numeric_limits<double>::epsilon());
    ad::DualNumber left_num = ad::log(spot / strike);
    ad::DualNumber r1 = ad::DualNumber(0.5) * volatility * volatility;
    ad::DualNumber right_num = (interestRate + r1) * maturity;
    ad::DualNumber denom = volatility * ad::sqrt(maturity);
    ad::DualNumber d1 = (left_num + right_num)
        / denom;
    ad::DualNumber d2 = d1 - volatility * ad::sqrt(maturity);
    math::distribution::StandardNormal d = math::distribution::StandardNormal();
    ad::DualNumber discountFactor = ad::exp(ad::DualNumber(-1.0) * interestRate * maturity);
    return spot * d.cdf(d1) - strike * discountFactor * d.cdf(d2);
}

template<int DIM>
ad::dual_number<DIM> black(
    ad::dual_number<DIM>& interestRate,
    ad::dual_number<DIM>& volatility,
    ad::dual_number<DIM>& maturity,
    ad::dual_number<DIM>& spot,
    ad::dual_number<DIM>& strike)
{
    assert(volatility.getValue() > std::numeric_limits<double>::epsilon());
    ad::dual_number<DIM> left_num = ad::log<DIM>(spot / strike);
    ad::dual_number<DIM> r1 = volatility * volatility * ad::dual_number<DIM>(0.5);
    ad::dual_number<DIM> right_num = (interestRate + r1) * maturity;
    ad::dual_number<DIM> denom = volatility * ad::sqrt<DIM>(maturity);
    ad::dual_number<DIM> d1 = (left_num + right_num) / denom;
    ad::dual_number<DIM> d2 = d1 - volatility * ad::sqrt<DIM>(maturity);
    math::distribution::StandardNormal d = math::distribution::StandardNormal();
    ad::dual_number<DIM> discountFactor = ad::exp<DIM>(interestRate * maturity * ad::dual_number<DIM>(-1.0));
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

void testSimpleOperator() {
    const double x = 3.0;
    ad::DualNumber xv = ad::DualNumber(x, 1.0);
    const double a = 2.0;
    ad::DualNumber av = ad::DualNumber(a);

    ad::DualNumber y = xv / xv;
    std::cout << y.getValue() << std::endl;
    std::cout << y.getDerivative() << std::endl;
}

void testBlack() {
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

    ad::DualNumber pv = black(interestRateV, volatilityV, maturityV, spotV, strikeV);
    std::cout << "Actual PV: " << pv.getValue() << std::endl;

    const double expectedDelta = blackDelta(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected Delta: " << expectedDelta << std::endl;

    std::cout << "Actual Delta: " << pv.getDerivative() << std::endl;
}

void testMultivarivateDual() {
    const double interestRate = 0.01;
    const double volatility = 0.1;
    const double maturity = 10.0;
    const double spot = 110.0;
    const double strike = 100.0;
    const std::size_t spotIndex = 0;
    const std::size_t volatilityIndex = 1;

    ad::dual_number<2> spotV(spot, spotIndex);
    ad::dual_number<2> volatilityV(volatility, volatilityIndex);
    ad::dual_number<2> interestRateV(interestRate);
    ad::dual_number<2> strikeV(strike);
    ad::dual_number<2> maturityV(maturity);

    ad::dual_number<2> z = spotV * spotV;
    std::cout << z.getValue() << std::endl;
    std::cout << z.getDerivatives()[0] << std::endl;

    const double expected = black(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected PV: " << expected << std::endl;

    ad::dual_number<2> pv = black(interestRateV, volatilityV, maturityV, spotV, strikeV);
    std::cout << "Actual PV: " << pv.getValue() << std::endl;
    const double expectedDelta = blackDelta(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected Delta: " << expectedDelta << std::endl;

    std::cout << "Actual Delta: " << pv.getDerivatives()[0] << std::endl;
}

int main(){
    //testBlack();
    testMultivarivateDual();
    int xxx = 0;
    std::cin >> xxx;

    return 0;
}
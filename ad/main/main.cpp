
#include <random>
#include <iostream>
#include <cassert>
#include "math/distribution.h"

#include "ad/DualNumber.h"
#include "ad/dual_number.h"
#include "ad/functions.h"

#include "finance/black.h"

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

    const double expected = fe::black(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected PV: " << expected << std::endl;

    ad::DualNumber pv = fe::black(interestRateV, volatilityV, maturityV, spotV, strikeV);
    std::cout << "Actual PV: " << pv.getValue() << std::endl;

    const double expectedDelta = fe::blackDelta(interestRate, volatility, maturity, spot, strike);
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

    const double expected = fe::black(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected PV: " << expected << std::endl;

    ad::dual_number<2> pv = fe::black(interestRateV, volatilityV, maturityV, spotV, strikeV);
    std::cout << "Actual PV: " << pv.getValue() << std::endl;
    const double expectedDelta = fe::blackDelta(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected Delta: " << expectedDelta << std::endl;

    std::cout << "Actual Delta: " << pv.getDerivatives()[0] << std::endl;

    const double expectedVega = fe::blackVega(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected Vega: " << expectedVega << std::endl;
    std::cout << "Actual Vega: " << pv.getDerivatives()[1] << std::endl;
}

void testMonteCarlo()
{
    const double interestRate = 0.01;
    const double volatility = 0.1;
    const double maturity = 10.0;
    const double spot = 110.0;
    const double strike = 100.0;
    
    // MC‚Í‚Ç‚±‚©‚ç‘‚«Žn‚ß‚ê‚Î‚æ‚¢‚©H
    const std::size_t numberOfSteps = 100;
    const std::size_t numberOfPaths = 100000;

    const double dt = maturity / numberOfSteps;
    const int seed = 100;
    std::mt19937 engine(seed);
    const double mean = 0.0;
    const double volatilityOfRandomness = 1.0;
    std::normal_distribution<> dist(mean, volatilityOfRandomness);
    double payoff = 0.0;
    for (std::size_t pathIndex = 0; pathIndex < numberOfPaths; ++pathIndex) {
        
        double this_spot = spot;

        for (std::size_t stepIndex = 0; stepIndex < numberOfSteps; ++stepIndex) {
            const double randomness = dist(engine);
            this_spot += interestRate * this_spot * dt + volatility * this_spot * randomness;
            //std::cout << this_spot << std::endl;
            //this_spot *= std::exp((interestRate - 0.5 * volatility * volatility)
            //    * dt + volatility * std::sqrt(dt) * randomness);
        }
        payoff += std::max(this_spot - strike, 0.0);
        std::cout << payoff << std::endl;
    }
    const double discountFactor = std::exp(-interestRate * maturity);
    const double presentValue = payoff / static_cast<double>(numberOfPaths) * discountFactor;
    const double expected = fe::black(interestRate, volatility, maturity, spot, strike);
    std::cout << "Expected Pv: " << expected << std::endl;
    std::cout << "Actual Pv: " << presentValue << std::endl;
}

int main(){
    //testBlack();
    //testMultivarivateDual();
    testMonteCarlo();

    int xxx = 0;
    std::cin >> xxx;

    return 0;
}
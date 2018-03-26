#include <cassert>
#include <cmath>

#include "black.h"
#include "math/distribution.h"
//#include "ad/DualNumber.h"
//#include "ad/dual_number.h"
#include "ad/functions.h"

namespace fe {
    double calculateD1(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike)
    {
        return (std::log(spot / strike) + (interestRate + 0.5 * volatility * volatility) * maturity)
            / (volatility * std::sqrt(maturity));
    }

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

    double blackDelta(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike)
    {
        const double d1 = calculateD1(interestRate, volatility, maturity, spot, strike);
        math::distribution::StandardNormal d = math::distribution::StandardNormal();
        return d.cdf(d1);
    }

    double blackVega(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike)
    {
        const double d1 = calculateD1(interestRate, volatility, maturity, spot, strike);
        math::distribution::StandardNormal d = math::distribution::StandardNormal();
        return spot * d.pdf(d1) * std::sqrt(maturity);
    }



}
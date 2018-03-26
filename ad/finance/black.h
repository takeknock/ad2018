#pragma once

#include "ad/macro.h"

#include "ad/DualNumber.h"
#include "ad/dual_number.h"

namespace fe {
    double calculateD1(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike);

    FE_API double black(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike);

    FE_API ad::DualNumber black(
        ad::DualNumber& interestRate,
        ad::DualNumber& volatility,
        ad::DualNumber& maturity,
        ad::DualNumber& spot,
        ad::DualNumber& strike);

    FE_API double blackDelta(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike);

    FE_API double blackVega(
        const double interestRate,
        const double volatility,
        const double maturity,
        const double spot,
        const double strike);

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

} // namespace fe {

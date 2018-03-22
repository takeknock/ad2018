#include <cmath>
#include "functions.h"

namespace math {
    ad::DualNumber log(const ad::DualNumber& d)
    {
        return ad::DualNumber(std::log(d.getValue()), 1.0 / d.getValue() * d.getDerivative());
    }

    ad::DualNumber sqrt(const ad::DualNumber& d)
    {
        return ad::DualNumber(std::sqrt(d.getValue()), 1.0 / (2.0 * std::sqrt(d.getValue())) * d.getDerivative());
    }

    ad::DualNumber exp(const ad::DualNumber& d)
    {
        return ad::DualNumber(std::exp(d.getValue()), std::exp(d.getValue()) * d.getDerivative());
    }

}
#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include "ad/DualNumber.h"


namespace math {
    namespace distribution {
        class Normal {
        public:
            double cdf(const double x, const double mean, const double volatility)
            {
                return 0.5 * (1.0 + std::erf((x - mean) / (std::sqrt(2.0) * volatility)));
            }

        };

        class StandardNormal {
        public:
            double cdf(const double x)
            {
                Normal d = Normal();
                return d.cdf(x, 0.0, 1.0);
            }

            ad::DualNumber cdf(ad::DualNumber& x)
            {
                ad::DualNumber s = ad::DualNumber(
                    cdf(x.getValue()),
                    1.0 / std::sqrt(2.0 * M_PI) * std::exp(-x.getValue() * x.getValue() / 2.0) * x.getDerivative());
                return ad::DualNumber(s);
            }
        };

    } // namespace distribution 
} // namespace math 

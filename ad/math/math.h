#pragma once

#include <cmath>

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
        };

    } // namespace distribution 
} // namespace math 

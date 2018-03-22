#include "distribution.h"

namespace math {
    namespace distribution {
        double Normal::cdf(const double x, const double mean, const double volatility)
        {
            return 0.5 * (1.0 + std::erf((x - mean) / (std::sqrt(2.0) * volatility)));
        }

        double StandardNormal::cdf(const double x)
        {
            Normal d = Normal();
            return d.cdf(x, 0.0, 1.0);
        }

        double StandardNormal::pdf(const double x)
        {
            return 1.0 / std::sqrt(2.0 * M_PI) * std::exp(-x * x / 2.0);
        }

        ad::DualNumber StandardNormal::cdf(ad::DualNumber& x)
        {
            ad::DualNumber s = ad::DualNumber(
                cdf(x.getValue()),
                pdf(x.getValue()) * x.getDerivative());
            return ad::DualNumber(s);
        }



    }

} // namespace math {
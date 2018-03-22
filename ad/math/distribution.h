#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include "ad/DualNumber.h"
#include "ad/dual_number.h"

#include "ad/macro.h"


namespace math {
    namespace distribution {
        class Normal {
        public:
            MATH_API double cdf(const double x, const double mean, const double volatility);
        };

        class StandardNormal {
        public:
            MATH_API double cdf(const double x);

            MATH_API double pdf(const double x);

            MATH_API ad::DualNumber cdf(ad::DualNumber& x);

            template<int DIM>
            ad::dual_number<DIM> cdf(ad::dual_number<DIM>& x)
            {
                std::array<double, DIM> derivatives = x.getDerivatives();
                //std::for_each(derivatives.begin(), derivatives.end(),
                //    [this, x](double derivative) { return pdf(x.getValue()) * derivative; });
                //std::transform(derivatives.begin(), derivatives.end(),
                //    std::back_inserter(derivatives),
                //    [this, x](double derivative) { return pdf(x.getValue()) * derivative; });
                for (std::size_t i = 0; i < DIM; ++i) {
                    derivatives[i] = pdf(x.getValue()) * derivatives[i];
                }

                return ad::dual_number<DIM>(cdf(x.getValue()), derivatives);
            }
        };

    } // namespace distribution 
} // namespace math 

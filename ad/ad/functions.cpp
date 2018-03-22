#include <cmath>
#include <array>
#include "functions.h"

namespace ad {
    DualNumber log(const DualNumber& d)
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

    //template<int DIM>
    //ad::dual_number<DIM> exp(const ad::dual_number<DIM>& d)
    //{
    //    std::array<double, DIM> derivatives = d.getDerivatives();

    //    //std::for_each(derivatives.begin(), derivatives.end(),
    //    //    [d](double derivative) { return derivative * std::exp(d.getValue()); });
    //    //std::transform(derivatives.begin(), derivatives.end(),
    //    //    std::back_inserter(result),
    //    //    [](double derivative) { return derivative * std::exp(d.getValue()); });
    //    for (std::size_t i = 0; i < DIM; ++i) {
    //        derivatives[i] *= std::exp(d.getValue());
    //    }

    //    return ad::dual_number<DIM>(std::exp(d.getValue()), derivatives);
    //}

    //template<int DIM>
    //ad::dual_number<DIM> sqrt(const ad::dual_number<DIM>& d)
    //{
    //    std::array<double, DIM> derivatives = d.getDerivatives();

    //    //std::for_each(derivatives.begin(), derivatives.end(),
    //    //    [d](double derivative) { return derivative / (2.0 * std::sqrt(d.getValue())); });
    //    //std::transform(derivatives.begin(), derivatives.end(),
    //    //    std::back_inserter(result),
    //    //    [](double derivative) { return derivative / (2.0 * std::sqrt(d.getValue()); }));
    //    for (std::size_t i = 0; i < DIM; ++i) {
    //        derivatives[i] *= 1.0 / (2.0 * std::sqrt(d.getValue()));
    //    }
    //    return ad::dual_number<DIM>(std::sqrt(d.getValue()), derivatives);
    //}

    //template<int DIM>
    //ad::dual_number<DIM> log(const ad::dual_number<DIM>& d)
    //{
    //    std::array<double, DIM> derivatives = d.getDerivatives();
    //    //std::for_each(derivatives.begin(), derivatives.end(),
    //    //    [d](double derivative) { return derivative / d.getValue(); });
    //    //std::transform(derivatives.begin(), derivatives.end(),
    //    //    std::back_inserter(result),
    //    //    [](double derivative) { return derivative / d.getValue(); });
    //    for (std::size_t i = 0; i < DIM; ++i) {
    //        derivatives[i] /= d.getValue();
    //    }

    //    return ad::dual_number<DIM>(std::log(d.getValue()), derivatives);
    //}



}
#pragma once
#include "macro.h"

namespace ad {
    class DualNumber {
    public:
        //DualNumber();
        AD_API DualNumber(const DualNumber& rhs) = default;
        DualNumber(DualNumber&& rhs) = default;
        AD_API DualNumber operator =(const DualNumber& rhs);
        DualNumber& operator =(DualNumber&& rhs) = default;
        AD_API DualNumber(const double value, const double derivative = 0.0);
        DualNumber& operator+=(const DualNumber& rhs);
        DualNumber& operator-=(const DualNumber& rhs);
        DualNumber& operator*=(const DualNumber& rhs);
        DualNumber& operator/=(const DualNumber& rhs);
        AD_API DualNumber operator +(const DualNumber& rhs);
        AD_API DualNumber operator -(const DualNumber& rhs);
        AD_API DualNumber operator *(const DualNumber& rhs);
        AD_API DualNumber operator /(const DualNumber& rhs);

        AD_API double getValue() const;
        AD_API double getDerivative() const;

    private:
        double _e;
        double _derivative;

    };
} // namespace ad {


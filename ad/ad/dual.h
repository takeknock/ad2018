#pragma once
#include "macro.h"

namespace ad {
    class dual {
    public:
        //dual();
        AD_API dual(const dual& rhs) = default;
        dual(dual&& rhs) = default;
        AD_API dual operator =(const dual& rhs);
        dual& operator =(dual&& rhs) = default;
        AD_API dual(const double value, const double derivative = 0.0);
        dual& operator+=(const dual& rhs);
        dual& operator-=(const dual& rhs);
        dual& operator*=(const dual& rhs);
        dual& operator/=(const dual& rhs);
        AD_API dual operator +(const dual& rhs);
        AD_API dual operator -(const dual& rhs);
        AD_API dual operator *(const dual& rhs);
        AD_API dual operator /(const dual& rhs);

        AD_API double getValue() const;
        AD_API double getDerivative() const;

    private:
        double _e;
        double _derivative;

    };
} // namespace ad {


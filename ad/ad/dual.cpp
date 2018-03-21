#include <iostream>
#include <cassert>
#include "dual.h"

namespace ad {
    //dual::dual()
    //{}

    //dual::dual(dual&& rhs)
    //{}

    dual dual::operator =(const dual& rhs)
    {
        return dual(rhs);
    }

    dual::dual(const double value, const double derivative)
    :_e(value), _derivative(derivative)
    {}

    dual&  dual::operator+=(const dual& rhs)
    {
        _e += rhs.getValue();
        _derivative += rhs.getDerivative();
        return *this;
    }
    dual& dual::operator-=(const dual& rhs)
    {
        _e -= rhs.getValue();
        _derivative -= rhs.getDerivative();
        return *this;
    }
    dual& dual::operator*=(const dual& rhs)
    {
        _e *= rhs.getValue();
        _derivative = _e * rhs.getDerivative() + _derivative * rhs.getValue();
        return *this;
    }
    dual& dual::operator/=(const dual& rhs)
    {
        assert(rhs.getValue() - 0.0 < std::numeric_limits<double>::epsilon());
        const double rhsValue = rhs.getValue();
        _e /= rhsValue;
        _derivative = (_e * rhs.getDerivative() + _derivative * rhsValue) / (rhsValue * rhsValue);
        return *this;
    }

    dual dual::operator +(const dual& rhs)
    {
        return dual(*this) += rhs;
    }

    dual dual::operator -(const dual& rhs)
    {
        return dual(*this) -= rhs;
    }

    dual dual::operator *(const dual& rhs)
    {
        return dual(*this) *= rhs;
    }

    dual dual::operator /(const dual& rhs)
    {
        return dual(*this) /= rhs;
    }

    double dual::getValue() const
    {
        return _e;
    }

    double dual::getDerivative() const
    {
        return _derivative;
    }

}// namespace ad {


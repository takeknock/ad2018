#include <iostream>
#include <cassert>
#include "DualNumber.h"

namespace ad {
    //DualNumber::DualNumber()
    //{}

    //DualNumber::DualNumber(DualNumber&& rhs)
    //{}

    DualNumber DualNumber::operator =(const DualNumber& rhs)
    {
        return DualNumber(rhs);
    }

    DualNumber::DualNumber(const double value, const double derivative)
    :_e(value), _derivative(derivative)
    {}

    DualNumber&  DualNumber::operator+=(const DualNumber& rhs)
    {
        _e += rhs.getValue();
        _derivative += rhs.getDerivative();
        return *this;
    }
    DualNumber& DualNumber::operator-=(const DualNumber& rhs)
    {
        _e -= rhs.getValue();
        _derivative -= rhs.getDerivative();
        return *this;
    }
    DualNumber& DualNumber::operator*=(const DualNumber& rhs)
    {
        const double tempE = _e;
        _e *= rhs.getValue();
        _derivative = tempE * rhs.getDerivative() + _derivative * rhs.getValue();
        return *this;
    }
    DualNumber& DualNumber::operator/=(const DualNumber& rhs)
    {
        assert(rhs.getValue() > std::numeric_limits<double>::epsilon());
        const double rhsValue = rhs.getValue();
        const double tempE = _e;
        _e /= rhsValue;
        _derivative = (_derivative * rhsValue - tempE * rhs.getDerivative()) / (rhsValue * rhsValue);
        return *this;
    }

    DualNumber DualNumber::operator +(const DualNumber& rhs)
    {
        return DualNumber(*this) += rhs;
    }

    DualNumber DualNumber::operator -(const DualNumber& rhs)
    {
        return DualNumber(*this) -= rhs;
    }

    DualNumber DualNumber::operator *(const DualNumber& rhs)
    {
        return DualNumber(*this) *= rhs;
    }

    DualNumber DualNumber::operator /(const DualNumber& rhs)
    {
        return DualNumber(*this) /= rhs;
    }

    double DualNumber::getValue() const
    {
        return _e;
    }

    double DualNumber::getDerivative() const
    {
        return _derivative;
    }

}// namespace ad {


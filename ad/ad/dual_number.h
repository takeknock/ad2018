#pragma once
#include <array>
#include "macro.h"

namespace ad {
    template<int DIM>
    class dual_number {
    public:
        dual_number<DIM>(const double value);
        dual_number<DIM>(const dual_number<DIM>& rhs);
        dual_number<DIM>(const double value, const std::array<double, DIM> derivatives);
        dual_number<DIM>(dual_number<DIM>&& rhs) = default;
        dual_number<DIM> operator =(const dual_number& rhs);
        dual_number<DIM>& operator =(dual_number<DIM>&& rhs) = default;
        dual_number<DIM>(const double value, const std::size_t index);
        dual_number<DIM>& operator+=(const dual_number<DIM>& rhs);
        dual_number<DIM>& operator-=(const dual_number<DIM>& rhs);
        dual_number<DIM>& operator*=(const dual_number<DIM>& rhs);
        dual_number<DIM>& operator/=(const dual_number<DIM>& rhs);
        dual_number<DIM> operator +(const dual_number<DIM>& rhs);
        dual_number<DIM> operator -(const dual_number<DIM>& rhs);
        dual_number<DIM> operator *(const dual_number<DIM>& rhs);
        dual_number<DIM> operator /(const dual_number<DIM>& rhs);

        dual_number<DIM>& operator*=(const double rhs);
        dual_number<DIM> operator *(const double rhs);

        double getValue() const;
        std::array<double, DIM> getDerivatives() const;

    private:
        double _e;
        std::array<double, DIM> _derivatives = std::array<double, DIM>();
    };

    template<int DIM>
    dual_number<DIM>::dual_number<DIM>(const double value)
    {
        _e = value;
        std::fill(_derivatives.begin(), _derivatives.end(), 0.0);
    }

    template<int DIM>
    dual_number<DIM>::dual_number<DIM>(const dual_number<DIM>& rhs)
    :_e(rhs.getValue()), _derivatives(rhs.getDerivatives())
    {
    }

    template<int DIM>
    dual_number<DIM>::dual_number<DIM>(
        const double value, 
        const std::array<double, DIM> derivatives)
     :_e(value), _derivatives(derivatives)
    {
    }

    template<int DIM>
    dual_number<DIM>::dual_number<DIM>(const double value, const std::size_t index)
    {
        assert(index < DIM);
        _e = value;
        std::fill(_derivatives.begin(), _derivatives.end(), 0.0);
        _derivatives[index] = 1.0;
    }

    template<int DIM>
    dual_number<DIM> dual_number<DIM>::operator =(const dual_number<DIM>& rhs)
    {
        return dual_number<DIM>(rhs);
    }

    template<int DIM>
    dual_number<DIM>& dual_number<DIM>::operator+=(const dual_number<DIM>& rhs)
    {
        _e += rhs.getValue();
        for (int i = 0; i < DIM; ++i) {
            _derivatives[i] += rhs.getDerivatives()[i];
        }
        return *this;
    }

    template<int DIM>
    dual_number<DIM>& dual_number<DIM>::operator-=(const dual_number<DIM>& rhs)
    {
        _e -= rhs.getValue();
        for (int i = 0; i < DIM; ++i) {
            _derivatives[i] -= rhs.getDerivatives()[i];
        }
        return *this;
    }

    template<int DIM>
    dual_number<DIM>& dual_number<DIM>::operator*=(const dual_number<DIM>& rhs)
    {
        const double tempValue = _e;
        _e *= rhs.getValue();
        for (int i = 0; i < DIM; ++i) {
            _derivatives[i] = tempValue * rhs.getDerivatives()[i] + _derivatives[i] * rhs.getValue();
        }
        return *this;
    }

    template<int DIM>
    dual_number<DIM>& dual_number<DIM>::operator/=(const dual_number<DIM>& rhs)
    {
        const double tempValue = _e;
        const double rhsValue = rhs.getValue();
        _e /= rhsValue;
        
        for (int i = 0; i < DIM; ++i) {
            _derivatives[i] = (_derivatives[i] * rhsValue - tempValue * rhs.getDerivatives()[i]) / (rhsValue * rhsValue);
        }
        return *this;
    }

    template<int DIM>
    dual_number<DIM>& dual_number<DIM>::operator*=(const double rhs)
    {
        const double tempValue = _e;
        _e *= rhs;
        for (int i = 0; i < DIM; ++i) {
            _derivatives[i] *= rhs;
        }
        return *this;
    }

    template<int DIM>
    dual_number<DIM> dual_number<DIM>::operator +(const dual_number<DIM>& rhs)
    {
        return dual_number<DIM>(*this) += rhs;
    }

    template<int DIM>
    dual_number<DIM> dual_number<DIM>::operator -(const dual_number<DIM>& rhs)
    {
        return dual_number<DIM>(*this) -= rhs;
    }

    template<int DIM>
    dual_number<DIM> dual_number<DIM>::operator *(const dual_number<DIM>& rhs)
    {
        return dual_number<DIM>(*this) *= rhs;
    }

    template<int DIM>
    dual_number<DIM> dual_number<DIM>::operator /(const dual_number<DIM>& rhs)
    {
        return dual_number<DIM>(*this) /= rhs;
    }

    template<int DIM>
    dual_number<DIM> dual_number<DIM>::operator *(const double rhs)
    {
        return dual_number<DIM>(*this) *= rhs;
    }

    template<int DIM>
    double dual_number<DIM>::getValue() const
    {
        return _e;
    }

    template<int DIM>
    std::array<double, DIM> dual_number<DIM>::getDerivatives() const
    {
        return _derivatives;
    }
    template<int DIM>
    ad::dual_number<DIM> exp(const ad::dual_number<DIM>& d)
    {
        std::array<double, DIM> derivatives = d.getDerivatives();

        //std::for_each(derivatives.begin(), derivatives.end(),
        //    [d](double derivative) { return derivative * std::exp(d.getValue()); });
        for (std::size_t i = 0; i < DIM; ++i) {
            derivatives[i] *= std::exp(d.getValue());
        }

        return ad::dual_number<DIM>(std::exp(d.getValue()), derivatives);
    }

    template<int DIM>
    ad::dual_number<DIM> sqrt(const ad::dual_number<DIM>& d)
    {
        std::array<double, DIM> derivatives = d.getDerivatives();

        //std::for_each(derivatives.begin(), derivatives.end(),
        //    [d](double derivative) { return derivative / (2.0 * std::sqrt(d.getValue())); });
        for (std::size_t i = 0; i < DIM; ++i) {
            derivatives[i] *= 1.0 / (2.0 * std::sqrt(d.getValue()));
        }
        return ad::dual_number<DIM>(std::sqrt(d.getValue()), derivatives);
    }

    template<int DIM>
    ad::dual_number<DIM> log(const ad::dual_number<DIM>& d)
    {
        std::array<double, DIM> derivatives = d.getDerivatives();
        //std::for_each(derivatives.begin(), derivatives.end(),
        //    [d](double derivative) { return derivative / d.getValue(); });
        for (std::size_t i = 0; i < DIM; ++i) {
            derivatives[i] /= d.getValue();
        }

        return ad::dual_number<DIM>(std::log(d.getValue()), derivatives);
    }


} // namespace ad {
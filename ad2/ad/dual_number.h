#pragma once

namespace ad {
    template <int DIM>
    class dual_number {
    public:
        dual_number<DIM>();
        //dual_number<DIM>(const double x, const int index);
        dual_number<DIM>::dual_number<DIM>(const double x, const int index)
        : _value(x), _derivatives[index](1.0)
        {
        }

        dual_number<DIM>(const dual_number<DIM>& other);
        dual_number<DIM>(dual_number<DIM>&& other);

        dual_number<DIM> operator =(const dual_number<DIM>& other);
        dual_number<DIM> operator =(dual_number<DIM>&& other);

        dual_number<DIM> operator+=(const dual_number<DIM>& rhs);
        dual_number<DIM> operator-=(const dual_number<DIM>& rhs);
        dual_number<DIM> operator*=(const dual_number<DIM>& rhs);
        dual_number<DIM> operator/=(const dual_number<DIM>& rhs);

        dual_number<DIM> operator +(const dual_number<DIM>& rhs);
        dual_number<DIM> operator -(const dual_number<DIM>& rhs);
        dual_number<DIM> operator *(const dual_number<DIM>& rhs);
        dual_number<DIM> operator /(const dual_number<DIM>& rhs);

        double getValue() const 
        {
            return _value;
        }

        std::array<double, DIM> getDerivatives() const
        {
            return _derivatives;
        }


    private:
        double _value;
        std::array<double, int> _derivatives = std::vector<double, DIM>();

    };


    dual_number<DIM>::dual_number<DIM>()
    {}

    //dual_number<DIM>::dual_number<DIM>(const double x, const int index)
    //:_value(x)
    //{
    //    //*this->_value = x;
    //    _derivatives[index] = 1.0;
    //}

    template <int DIM>
    dual_number<DIM>::dual_number<DIM>(const dual_number<DIM>& other)
    {
        *this._value = other.getValue();
        _derivatives = other.getDerivatives();
    }

    dual_number<DIM>::dual_number<DIM>(dual_number<DIM>&& other)
    {}

    template <int DIM>
    dual_number<DIM> dual_number<DIM>::operator =(const dual_number<DIM>& other)
    {
        *this.value = other.getValue();
        return *this;
    }

    dual_number<DIM> dual_number<DIM>::operator =(dual_number<DIM>&& other)
    {
        *this = other;
        return *this;
    }

    dual_number<DIM>& dual_number<DIM>::operator+=(const dual_number<DIM>& rhs)
    {
        *this.value += other.getValue();

        return *this;
    }




} // namespace ad {


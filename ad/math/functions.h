#pragma once
#include "ad/macro.h"
#include "ad/DualNumber.h"

namespace math {
    MATH_API ad::DualNumber log(const ad::DualNumber& d);
    MATH_API ad::DualNumber sqrt(const ad::DualNumber& d);
    MATH_API ad::DualNumber exp(const ad::DualNumber& d);
    
}
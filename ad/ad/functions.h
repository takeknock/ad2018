#pragma once
#include "macro.h"
#include "DualNumber.h"
#include "dual_number.h"

namespace ad {
    AD_API DualNumber log(const ad::DualNumber& d);
    AD_API DualNumber sqrt(const ad::DualNumber& d);
    AD_API DualNumber exp(const ad::DualNumber& d);
    
    //template<int DIM>
    //AD_API ad::dual_number<DIM> log(const ad::dual_number<DIM>& d);

    //template<int DIM>
    //AD_API ad::dual_number<DIM> sqrt(const ad::dual_number<DIM>& d);

    //template<int DIM>
    //AD_API ad::dual_number<DIM> exp(const ad::dual_number<DIM>& d);

    //template<int DIM>
    //ad::dual_number<DIM> cdf(const ad::dual_number<DIM>& d);

}
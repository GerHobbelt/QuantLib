/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015, 2024 Peter Caspers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file laplaceinterpolation.hpp
    \brief Laplace interpolation of missing values
*/

#ifndef quantlib_laplace_interpolation
#define quantlib_laplace_interpolation

#include <ql/types.hpp>
#include <vector>

namespace QuantLib {

    class FdmLinearOpLayout;

    /*! Reconstruction of missing values using Laplace interpolation. We support an arbitrary number
       of dimensions n >= 1 and non-equidistant grids. For n = 1 the method is identical  to linear
       interpolation. Reference: Numerical Recipes, 3rd edition, ch. 3.8. */

    class LaplaceInterpolation {
      public:
        /*! Missing values y should be encoded as Null<Real>(). */
        LaplaceInterpolation(std::function<Real(const std::vector<Size>&)> y,
                             std::vector<std::vector<Real>> x,
                             const Real relTol = 1E-6);
        Real operator()(const std::vector<Size>& coordinates) const;

      private:
        std::function<Real(const std::vector<Size>&)> y_;
        std::vector<std::vector<Real>> x_;
        boost::shared_ptr<FdmLinearOpLayout> layout_;
        Array interpolatedValues_; 
        Real relTol_;
    };

    /*! Convenience function that Laplace-interpolates null values in a given matrix.
        If the x or y grid or both are not given, an equidistant grid is assumed. */

    template <class M>
    void laplaceInterpolation(M& A,
                              Real relTol = 1E-6,
                              const std::vector<Real>& x = {},
                              const std::vector<Real>& y = {});
}

#endif

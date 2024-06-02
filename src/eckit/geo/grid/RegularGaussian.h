/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#pragma once

#include "eckit/geo/grid/Regular.h"


namespace eckit::geo::grid {


struct RegularGaussian final : public Regular {
    explicit RegularGaussian(const Spec&);
    explicit RegularGaussian(size_t N, const area::BoundingBox& = {});

    [[nodiscard]] static Spec* spec(const std::string& name);
    void spec(spec::Custom&) const override;

    size_t N() const { return N_; }

    [[nodiscard]] Grid* make_grid_cropped(const Area&) const override;

private:
    const size_t N_;
};


}  // namespace eckit::geo::grid

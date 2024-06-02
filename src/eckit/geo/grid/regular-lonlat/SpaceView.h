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

#include "eckit/geo/grid/RegularLonLat.h"


namespace eckit::geo::grid::regularlonlat {


struct SpaceView final : public RegularLonLat {
    explicit SpaceView(const Spec& spec) :
        RegularLonLat(RegularLonLat::make_cartesian_ranges_from_spec(spec), area::BoundingBox{spec}) {}

    void spec(spec::Custom& custom) const override;
};


}  // namespace eckit::geo::grid::regularlonlat

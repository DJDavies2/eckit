/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef GreatCircle_H
#define GreatCircle_H

#include <vector>

#include "eckit/geo/PointLonLat.h"

//------------------------------------------------------------------------------------------------------

namespace eckit::geo {

//------------------------------------------------------------------------------------------------------

class GreatCircle {
public:
    /// Great circle given two points in geographic coordinates
    GreatCircle(const PointLonLat&, const PointLonLat&);

    /// Great circle latitude given longitude, see http://www.edwilliams.org/avform.htm#Int
    std::vector<double> latitude(double lon) const;

    /// Great circle longitude given latitude, see http://www.edwilliams.org/avform.htm#Par
    std::vector<double> longitude(double lat) const;

    bool crossesPoles() const;

private:
    const PointLonLat A_;
    const PointLonLat B_;

    bool crossesPoles_;
};

//------------------------------------------------------------------------------------------------------

}  // namespace eckit::geo

#endif

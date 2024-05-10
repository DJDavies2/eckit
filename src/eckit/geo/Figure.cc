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


#include "eckit/geo/Figure.h"

#include <cmath>

#include "eckit/exception/Exceptions.h"
#include "eckit/geo/geometry/OblateSpheroid.h"


namespace eckit::geo {


double Figure::R() const {
    NOTIMP;
}


double Figure::a() const {
    NOTIMP;
}


double Figure::b() const {
    NOTIMP;
}


double Figure::eccentricity() const {
    return geometry::OblateSpheroid::eccentricity(a(), b());
}


}  // namespace eckit::geo

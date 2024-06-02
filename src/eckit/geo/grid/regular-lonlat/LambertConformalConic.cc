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


#include "eckit/geo/grid/regular-lonlat/LambertConformalConic.h"

#include "eckit/geo/spec/Custom.h"


namespace eckit::geo::grid::regularlonlat {


static const GridRegisterType<LambertConformalConic> GRIDTYPE("lambert");


void LambertConformalConic::spec(spec::Custom& custom) const {
    RegularLonLat::spec(custom);

    custom.set("type", "lambert");

    // FIXME a lot more stuff to add here!
    //...
}


}  // namespace eckit::geo::grid::regularlonlat

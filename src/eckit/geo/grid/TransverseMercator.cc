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


#include "eckit/geo/grid/TransverseMercator.h"

#include <ostream>


namespace eckit::geo::grid {


TransverseMercator::TransverseMercator(const Configuration& config) : RegularGrid(config){}


void TransverseMercator::print(std::ostream& out) const {
    out << "TransverseMercator["
        << "]";
}


static const GridBuilder<TransverseMercator> __repres("transverse_mercator");


}  // namespace eckit::geo::grid

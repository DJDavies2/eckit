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


#include "eckit/geo/grid/regular/XYToLonLat.h"

#include "eckit/exception/Exceptions.h"
#include "eckit/geo/Spec.h"
#include "eckit/geo/etc/Grid.h"
#include "eckit/geo/iterator/Regular.h"
#include "eckit/geo/spec/Custom.h"


namespace eckit::geo::grid::regular {


XYToLonLat::XYToLonLat(const Spec& spec) :
    XYToLonLat(Internal(spec)) {}


XYToLonLat::XYToLonLat(Internal&& internal) :
    internal_(internal) {}


XYToLonLat::XYToLonLat(double dx, double dy, size_t nx, size_t ny) :
    XYToLonLat(Internal{dx, dy, nx, ny}) {}


XYToLonLat::Internal::Internal(const Spec& spec) :
    grid{0., 0.}, shape{0, 0} {
    if (std::vector<size_t> value; spec.get("shape", value) && value.size() == 2) {
        shape = {value[0], value[1]};
    }
    else if (!spec.get("nx", shape[0]) || !spec.get("ny", shape[1])) {
        throw SpecNotFound("'shape': ['nx', 'ny'] expected");
    }

    if (std::vector<double> value; spec.get("grid", value) && value.size() == 2) {
        grid = {value[0], value[1]};
    }
    else if (!spec.get("dx", grid[0]) || !spec.get("dy", grid[1])) {
        throw SpecNotFound("'grid': ['dx', 'dy'] expected");
    }

    check();
}

XYToLonLat::Internal::Internal(double dx, double dy, size_t nx, size_t ny) :
    grid{dx, dy}, shape{nx, ny} {
    check();
}


void XYToLonLat::Internal::check() const {
    ASSERT_MSG(grid[0] > 0 && grid[1] > 0,
               "'grid' > 0 failed, got grid: [" + std::to_string(grid[0]) + ", " + std::to_string(grid[0]) + "]");
    ASSERT_MSG(shape[0] > 0 && shape[1] > 0,
               "'shape' > 0 failed, got shape: [" + std::to_string(shape[0]) + ", " + std::to_string(shape[0]) + "]");
}


Grid::iterator XYToLonLat::cbegin() const {
    return iterator{new geo::iterator::Regular(*this, 0)};
}


Grid::iterator XYToLonLat::cend() const {
    return iterator{new geo::iterator::Regular(*this, size())};
}


const std::vector<double>& XYToLonLat::longitudes() const {
    NOTIMP;
}


const std::vector<double>& XYToLonLat::latitudes() const {
    NOTIMP;
}


static const GridRegisterType<LambertAzimuthalEqualArea> __grid_type1("lambert_azimuthal_equal_area");
static const GridRegisterType<Mercator> __grid_type2("mercator");


void Mercator::spec(spec::Custom& custom) const {
    custom.set("type", "mercator");
    custom.set("grid", std::vector<double>{dj(), di()});
    custom.set("shape", std::vector<long>{static_cast<long>(nj()), static_cast<long>(ni())});

    // FIXME a lot more stuff to add here!
    //...

    if (std::string name; SpecByName::instance().match(custom, name)) {
        custom.clear();
        custom.set("grid", name);
    }
}


void LambertAzimuthalEqualArea::spec(spec::Custom& custom) const {
    custom.set("type", "lambert_azimuthal_equal_area");
    custom.set("grid", std::vector<double>{dj(), di()});
    custom.set("shape", std::vector<long>{static_cast<long>(nj()), static_cast<long>(ni())});

    // FIXME a lot more stuff to add here!
    //...

    if (std::string name; SpecByName::instance().match(custom, name)) {
        custom.clear();
        custom.set("grid", name);
    }
}


}  // namespace eckit::geo::grid::regular

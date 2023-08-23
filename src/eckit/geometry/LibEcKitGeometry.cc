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


#include "eckit/geometry/LibEcKitGeometry.h"

#include "eckit/config/Resource.h"
#include "eckit/eckit_version.h"
#include "eckit/filesystem/PathName.h"
#include "eckit/geometry/eckit_geometry_config.h"


namespace eckit {


REGISTER_LIBRARY(LibEcKitGeometry);


LibEcKitGeometry::LibEcKitGeometry() :
    Library("eckit_geometry") {}


LibEcKitGeometry& LibEcKitGeometry::instance() {
    static LibEcKitGeometry lib;
    return lib;
}


PathName LibEcKitGeometry::configFileGrid() {
    static const PathName path{LibResource<std::string, LibEcKitGeometry>("eckit-geometry-grid;$ECKIT_GEOMETRY_GRID", "~eckit/etc/eckit/geometry/grid.yaml")};
    return path;
}


bool LibEcKitGeometry::caching() {
    static const bool yes{LibResource<bool, LibEcKitGeometry>("eckit-geometry-caching;$ECKIT_GEOMETRY_CACHING", eckit_HAVE_GEOMETRY_CACHING != 0 ? true : false)};
    return yes;
}


std::string LibEcKitGeometry::cacheDir() {
    static std::string path = PathName{LibResource<PathName, LibEcKitGeometry>("eckit-geometry-cache-path;$ECKIT_GEOMETRY_CACHE_PATH", eckit_GEOMETRY_CACHE_PATH)};
    return path;
}


const void* LibEcKitGeometry::addr() const {
    return this;
}


std::string LibEcKitGeometry::version() const {
    return eckit_version_str();
}


std::string LibEcKitGeometry::gitsha1(unsigned int count) const {
    std::string sha1(eckit_git_sha1());
    return sha1.empty() ? "not available" : sha1.substr(0, std::min(count, 40U));
}


}  // namespace eckit

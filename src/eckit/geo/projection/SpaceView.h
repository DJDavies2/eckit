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

#include "eckit/geo/Projection.h"


namespace eckit::geo::projection {


/**
 * @brief SpaceView projection
 * @ref LRIT/HRIT Global Specification (CGMS 03, Issue 2.6, 12.08.1999)
 */
class SpaceView final : public Projection {
public:
    // -- Types
    // None

    // -- Exceptions
    // None

    // -- Constructors

    explicit SpaceView(const Spec&);

    // -- Destructor
    // None

    // -- Convertors
    // None

    // -- Operators
    // None

    // -- Methods
    // None

    // -- Overridden methods

    Point fwd(const Point&) const override;
    Point inv(const Point&) const override;

    [[nodiscard]] Spec* spec() const override;

    // -- Class members
    // None

    // -- Class methods
    // None

private:
    // -- Members
    // None

    // -- Methods
    // None

    // -- Overridden methods
    // None

    // -- Class members
    // None

    // -- Class methods
    // None

    // -- Friends
    // None
};


}  // namespace eckit::geo::projection

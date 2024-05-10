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

#include <string>

#include "eckit/exception/Exceptions.h"
#include "eckit/geo/Point.h"
#include "eckit/memory/Builder.h"
#include "eckit/memory/Factory.h"


namespace eckit::geo {
class Spec;
namespace spec {
class Custom;
}
}  // namespace eckit::geo


namespace eckit::geo {


class ProjectionProblem : public Exception {
public:
    explicit ProjectionProblem(const std::string&, const CodeLocation&);
};


class Projection {
public:
    // -- Types

    using builder_t = BuilderT1<Projection>;
    using ARG1      = const Spec&;

    // -- Constructors

    Projection() noexcept         = default;
    Projection(const Projection&) = default;
    Projection(Projection&&)      = default;

    // -- Destructor

    virtual ~Projection() = default;

    // -- Operators

    Projection& operator=(const Projection&) = default;
    Projection& operator=(Projection&&)      = default;

    // -- Methods

    static std::string className() { return "projection"; }

    virtual Point fwd(const Point&) const = 0;
    virtual Point inv(const Point&) const = 0;

    [[nodiscard]] virtual Spec* spec() const = 0;
};


using ProjectionFactory = Factory<Projection>;

template <typename T>
using ProjectionBuilder = ConcreteBuilderT1<Projection, T>;


}  // namespace eckit::geo

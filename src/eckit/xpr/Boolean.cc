/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/xpr/Boolean.h"
#include "eckit/xpr/Scope.h"

namespace eckit {
namespace xpr {

//--------------------------------------------------------------------------------------------

Boolean::Boolean( const Boolean::value_t& v ) : v_(v)
{
}

void Boolean::print(std::ostream&o) const
{
    o << nodeName() << "(" << (v_? "true" : "false") << ")";
}

void Boolean::asCode(std::ostream&o) const
{
    o << "xpr::boolean(" << (v_? "true" : "false") << ")";
}

Boolean::Boolean(const ExpPtr& e) : v_(0)
{
   Scope dummy("Boolean::Boolean");
   v_ = Boolean::extract( dummy, e->eval(dummy) );
}

ExpPtr Boolean::cloneWith(args_t& a) const
{
    NOTIMP; // Should not be called
}

//--------------------------------------------------------------------------------------------

ExpPtr boolean(const Boolean::value_t &s)
{
    return ExpPtr( new Boolean(s) );
}

//--------------------------------------------------------------------------------------------

} // namespace xpr
} // namespace eckit

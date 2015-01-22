/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @file Boolean.h
/// @author Tiago Quintino
/// @date November 2013

#ifndef eckit_xpr_Boolean_h
#define eckit_xpr_Boolean_h

#include "eckit/xpr/Value.h"

namespace eckit {
namespace xpr {

//--------------------------------------------------------------------------------------------

class Boolean : public Value {

public: // static methods

    typedef bool value_t;

    static std::string sig() { return "b"; }
    static std::string nodeName() { return "Boolean"; }

    static scalar_t extract ( Scope& ctx , const ExpPtr& e )
    {
        return e->as<Boolean>()->value();
    }

public: // methods

    Boolean( const ExpPtr& e);

    Boolean( const value_t& v );

    /// @returns the value of the scalar
    value_t value() const { return v_; }

private: // virtual methods

    virtual std::string typeName() const { return nodeName(); }
    virtual std::string signature() const { return sig(); }
    virtual std::string returnSignature() const { return sig(); }

    virtual void print( std::ostream& o ) const;
    virtual void asCode( std::ostream& o ) const;
    virtual ExpPtr cloneWith(args_t& a) const;

protected: // members

    value_t v_;

};

//--------------------------------------------------------------------------------------------

// typedef SharedPtr<Boolean> BoolPtr;

/// Helper function to construct boolean expressions
ExpPtr boolean( const Boolean::value_t& s  );

//--------------------------------------------------------------------------------------------

} // namespace xpr
} // namespace eckit

#endif

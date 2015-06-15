/*
 * (C) Copyright 1996-2013 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/maths/Scalar.h"
#include "eckit/maths/Vector.h"
#include "eckit/maths/UnaryOperator.h"
#include "eckit/maths/Optimiser.h"

namespace eckit {
namespace maths {

//--------------------------------------------------------------------------------------------

                            \
ExpPtr neg( ExpPtr e )           { return ExpPtr( new UnaryOperator<Neg>(e) ); }

//--------------------------------------------------------------------------------------------

static const char *opname(const Neg&)  { return "Neg";  }
static const char *opsymbol(const Neg&)  { return "-";  }

//--------------------------------------------------------------------------------------------

struct Generic
{
    template <class T>
    static ExpPtr apply( T op, const Scalar::value_t& a )
    {
        return ExpPtr( new Scalar( op( a ) ) );
    }

    template <class T>
    static ExpPtr apply( T op, const Vector::value_t& v )
    {
        Vector::value_t rv( v.size() );

        for( size_t i = 0; i < rv.size(); ++i )
            rv[i] = op( v[i] );

        return ExpPtr( new Vector( rv, Vector::Swap() ));
    }
};

//--------------------------------------------------------------------------------------------

static UnaryOperator<Neg>::Computer<Scalar,Generic> neg_sg;
static UnaryOperator<Neg>::Computer<Vector,Generic> neg_vg;

//--------------------------------------------------------------------------------------------

template < class T >
UnaryOperator<T>::UnaryOperator(ExpPtr e)
{
    push_back(e);
}

template < class T >
UnaryOperator<T>::UnaryOperator(args_t& a) : Function(a)
{
    ASSERT( a.size() == 1 );
}

template < class T >
std::string UnaryOperator<T>::returnSignature() const
{
    return args(0)->returnSignature();
}

template < class T >
std::string UnaryOperator<T>::typeName() const
{
    return UnaryOperator<T>::className();
}

template < class T >
std::string UnaryOperator<T>::className()
{
    return opname( T() );
}

template < class T >
void UnaryOperator<T>::asCode( std::ostream& o ) const {
    o << opsymbol(T()) << '(' << *args(0) << ')';
}

/*
template < class T >
ExpPtr UnaryOperator<T>::optimise() const
{
    return Optimiser::apply(self());
}*/

template < class T >
template < class U, class I >
UnaryOperator<T>::Computer<U,I>::Computer()
{
    Function::dispatcher()[ sig() ] = &compute;
}

template < class T >
template < class U, class I >
std::string UnaryOperator<T>::Computer<U,I>::sig()
{
    return opname( T() ) + std::string("(") + U::sig() + std::string(")");
}

template < class T >
template < class U, class I >
ExpPtr UnaryOperator<T>::Computer<U,I>::compute(Scope& ctx, const args_t &p)
{
    typename U::value_t a = U::extract(ctx, p[0]);
    return I::apply(T(),a);
}

//--------------------------------------------------------------------------------------------

static OptimiseTo<Scalar> optimise_neg_s ( std::string(opname( Neg() )) + "(s)" );

//--------------------------------------------------------------------------------------------

} // namespace maths
} // namespace eckit
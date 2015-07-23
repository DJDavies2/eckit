/*
 * (C) Copyright 1996-2013 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File Prelude.cc
// Piotr Kuchta - (c) ECMWF July 2015

#include <string>

#include "experimental/eckit/ecml/parser/Request.h"

#include "experimental/eckit/ecml/core/RequestHandler.h"
#include "experimental/eckit/ecml/core/ExecutionContext.h"
#include "experimental/eckit/ecml/core/Environment.h"
#include "experimental/eckit/ecml/core/SpecialFormHandler.h"

#include "ListHandler.h"
#include "VariableLookupHandler.h"
#include "PrintHandler.h"

#include "LetHandler.h"
#include "DefineFunctionHandler.h"

#include "Prelude.h"

namespace eckit {

using namespace std;

Prelude::Prelude() {}
Prelude::~Prelude() {}

static Request native(const string& name) { return new Cell("_native", name, 0, 0); }
static Request macro(const string& name) { return new Cell("_macro", name, 0, 0); }

void Prelude::importInto(ExecutionContext& context)
{
    static DefineFunctionHandler function("function");
    static ListHandler list("list");
    static PrintHandler println("println", "\n");
    static PrintHandler print("print", "");
    static LetHandler let("let");
    static VariableLookupHandler value("value");

    Environment& e(context.environment());
    e.set("let", macro(let.name()));
    e.set("function", macro(function.name()));

    context.registerHandler("list", list);
    context.registerHandler("value", value);
    context.registerHandler("print", print);
    context.registerHandler("println", println);
}

} // namespace eckit
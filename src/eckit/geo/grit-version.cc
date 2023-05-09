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


#include <iostream>

#include "grit/grit.h"


int main(int /*argc*/, const char* /*argv*/[]) {
    std::cout << grit_VERSION_MAJOR << '.' << grit_VERSION_MINOR << '.' << grit_VERSION_PATCH << std::endl;
    return 0;
}

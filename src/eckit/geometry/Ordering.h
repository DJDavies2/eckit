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


namespace eckit::geometry {


enum Ordering
{
    scan_full_i_full_j_i_positively_j_negatively_j_consecutive_i_single_direction,
    scan_full_i_full_j_i_negatively_j_negatively_j_consecutive_i_single_direction,
    scan_full_i_full_j_i_positively_j_positively_j_consecutive_i_single_direction,
    scan_full_i_full_j_i_negatively_j_positively_j_consecutive_i_single_direction,
    scan_full_i_full_j_i_positively_j_negatively_i_consecutive_i_single_direction,
    scan_full_i_full_j_i_negatively_j_negatively_i_consecutive_i_single_direction,
    scan_full_i_full_j_i_positively_j_positively_i_consecutive_i_single_direction,
    scan_full_i_full_j_i_negatively_j_positively_i_consecutive_i_single_direction,
    scan_full_i_full_j_i_positively_j_negatively_j_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_negatively_j_negatively_j_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_positively_j_positively_j_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_negatively_j_positively_j_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_positively_j_negatively_i_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_negatively_j_negatively_i_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_positively_j_positively_i_consecutive_i_alternating_direction,
    scan_full_i_full_j_i_negatively_j_positively_i_consecutive_i_alternating_direction,
    // TODO scan_ ... shift

    scan_reduced_i_full_j_i_positively_j_negatively,
    scan_reduced_i_full_j_i_negatively_j_negatively,
    scan_reduced_i_full_j_i_positively_j_positively,
    scan_reduced_i_full_j_i_negatively_j_positively,
    // TODO scan_ ... shift

    healpix_ring,
    healpix_nested,
};


}  // namespace eckit::geometry

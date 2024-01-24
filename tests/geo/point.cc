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


#include "eckit/geo/Point.h"
#include "eckit/testing/Test.h"
#include "eckit/types/FloatCompare.h"


//----------------------------------------------------------------------------------------------------------------------


namespace eckit::test {


using namespace geo;


CASE("PointLonLat normalisation") {
    constexpr auto EPS = 1e-9;
    constexpr auto da  = 1e-3;

    for (double a = -370.; a < 370.; a += 10.) {
        EXPECT(types::is_approximately_equal(a, PointLonLat::normalise_angle_to_minimum(a, a), EPS));
        EXPECT(types::is_approximately_equal(a, PointLonLat::normalise_angle_to_maximum(a, a), EPS));
        EXPECT(types::is_approximately_equal(a + 360., PointLonLat::normalise_angle_to_minimum(a - da, a) + da, EPS));
        EXPECT(types::is_approximately_equal(a - 360., PointLonLat::normalise_angle_to_maximum(a + da, a) - da, EPS));
    }

    PointLonLat p(1, 90.);
    EXPECT_EQUAL(p.lon, 1.);
    EXPECT_EQUAL(p.lat, 90.);

    auto p2 = PointLonLat::make(p.lon, p.lat);
    EXPECT_EQUAL(p2.lon, 0.);
    EXPECT(points_equal(p, p2));

    auto p3 = PointLonLat(50., 90.);
    EXPECT(points_equal(p, p3));

    PointLonLat q(1., -90.);
    EXPECT_EQUAL(q.lon, 1.);
    EXPECT_EQUAL(q.lat, -90.);

    auto q2 = q.antipode();
    EXPECT_EQUAL(q2.lon, 0.);
    EXPECT(points_equal(q2, p));

    auto q3 = q2.antipode();
    EXPECT(points_equal(q3, q));
}


CASE("PointLonLat comparison") {
    auto r(PointLonLat::make(-10., -91.));
    EXPECT(points_equal(r, r.antipode().antipode()));

    Point a1 = PointLonLat{300, -30};
    Point a2 = PointLonLat{-59.99999999999996, -30.000000000000018};
    EXPECT(points_equal(a1, a2));

    Point b1 = PointLonLat{-178., -46.7};
    Point b2 = PointLonLat{-178.00000000000003, -46.7};
    EXPECT(points_equal(b1, b2));
}


CASE("Inits to Zero") {
    Point2 q;

    EXPECT(q[XX] == 0.);
    EXPECT(q[YY] == 0.);
}


CASE("Inits to Array/Point") {
    Point2 q = {4.0, 5.0};

    EXPECT(q[XX] == 4.0);
    EXPECT(q[YY] == 5.0);

    EXPECT(q[LON] == 4.0);
    EXPECT(q[LAT] == 5.0);

    Point2 r(q);
    EXPECT(r[XX] == 4.0);
    EXPECT(r[YY] == 5.0);

    Point3 p = {1.0, 2.0, 3.0};
    Point3 s(p);
    EXPECT(s[XX] == 1.0);
    EXPECT(s[YY] == 2.0);
    EXPECT(s[ZZ] == 3.0);
}


CASE("Point2 addition") {
    Point2 p1 = {1.0, 2.0};
    Point2 p2 = {2.0, 4.0};

    Point2 r = p1 + p2;

    EXPECT(r[XX] == 3.0);
    EXPECT(r[YY] == 6.0);
}


CASE("Point2 subtraction") {
    Point2 p1 = {2.0, 5.0};
    Point2 p2 = {1.0, 2.0};

    Point2 r = p1 - p2;

    EXPECT(r[XX] == 1.0);
    EXPECT(r[YY] == 3.0);
}


CASE("Point2 scaling") {
    Point2 p1 = {1.0, 2.0};
    Point2 p2(p1);

    Point2 r = p1 * 42.0;

    EXPECT(r[XX] == 42.0);
    EXPECT(r[YY] == 84.0);

    Point2 oo;

    Point2 p3 = p2 * 2.0;
    Point2 p4 = p3 + p2;
    Point2 p5 = p4 - p2 * 3;
    EXPECT(p5 == oo);
}


CASE("Point2 equality") {
    Point2 p1 = {1.0, 2.0};
    Point2 p2 = {1.0, 2.0};

    EXPECT(p1 == p2);
}


CASE("Point2 inequality") {
    Point2 p1 = {1.0, 3.0};
    Point2 p2 = {1.0, 4.0};

    EXPECT(p1 != p2);
}


CASE("Point2 comparison") {
    Point2 p1 = {2.0, 1.0};
    Point2 p2 = {1.0, 2.0};

    // EXPECT(p2 < p1);
}


CASE("Point2 distance comparison") {
    Point2 p1 = {2.0, 1.0};
    Point2 p2 = {1.0, 2.0};

    EXPECT(types::is_approximately_equal(sqrt(2.0), p1.distance(p2)));

    Point2 p3 = {5.0, 5.0};

    EXPECT(types::is_approximately_equal(p1.distance(p3), 5.0));
}


CASE("Point2 distance2 comparison") {
    Point2 p1 = {2.0, 1.0};
    Point2 p2 = {1.0, 2.0};

    EXPECT(types::is_approximately_equal(p1.distance2(p2), 2.0));

    Point2 p3 = {5.0, 5.0};

    EXPECT(types::is_approximately_equal(p1.distance2(p3), 25.0));
}


CASE("Point3 cross") {
    Point3 p1 = {1.0, 0.0, 0.0};
    Point3 p2 = {0.0, 1.0, 0.0};
    Point3 p3 = {0.0, 0.0, 1.0};

    EXPECT(p3 == Point3::cross(p1, p2));
    EXPECT(p1 == Point3::cross(p2, p3));

    Point3 p4 = {1.0, 2.0, 3.0};
    Point3 p5 = {-1.0, -2.0, 4.0};
    Point3 p6 = {2.0, -1.0, 0.0};

    Point3 p7 = Point3::normalize(Point3::cross(p4, p5));
    Point3 p8 = Point3::normalize(p6);

    EXPECT(types::is_approximately_equal(p7[XX], p8[XX]));
    EXPECT(types::is_approximately_equal(p7[YY], p8[YY]));
    EXPECT(types::is_approximately_equal(p7[ZZ], p8[ZZ]));
}


}  // namespace eckit::test


//----------------------------------------------------------------------------------------------------------------------


int main(int argc, char** argv) {
    return eckit::testing::run_tests(argc, argv);
}

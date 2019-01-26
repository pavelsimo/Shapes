#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPoint tests")
{
    SECTION("geometry type")
    {
        MultiPoint mp;
        CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
        CHECK(mp.geom_type_str() == "MULTIPOINT");
    }

    SECTION("2d multipoint constructor - initializer list <double>")
    {
        MultiPoint mp = {{1.0, 2.0}, {2.0, 3.0}};
        CHECK(mp[0].x == 1.0);
        CHECK(mp[0].y == 2.0);
        CHECK(mp[1].x == 2.0);
        CHECK(mp[1].y == 3.0);
    }

    SECTION("3d multipoint constructor - initializer list <double>")
    {
        MultiPoint mp = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
        CHECK(mp[0].x == 1.0);
        CHECK(mp[0].y == 2.0);
        CHECK(mp[0].z == 3.0);
        CHECK(mp[1].x == 4.0);
        CHECK(mp[1].y == 5.0);
        CHECK(mp[1].z == 6.0);
    }

    SECTION("2d multipoint envelope")
    {
        MultiPoint mp = {{1.0, 2.0}, {3.0, 4.0}};
        CHECK(mp.envelope().max().x == 3.0);
        CHECK(mp.envelope().max().y == 4.0);
        CHECK(mp.envelope().min().x == 1.0);
        CHECK(mp.envelope().min().y == 2.0);
    }

    SECTION("2d multipoint for each")
    {
        auto points = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        int count = 0;
        for (const auto& point: points)
        {
            CHECK(point.x != 0);
            CHECK(point.y != 0);
            ++count;
        }
        CHECK(count == 3);
    }

    SECTION("3d multipoint for each")
    {
        auto points = MultiPoint{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
        int count = 0;
        for (const auto& point: points)
        {
            CHECK(point.x != 0);
            CHECK(point.y != 0);
            CHECK(point.z != 0);
            ++count;
        }
        CHECK(count == 3);
    }

    SECTION("2d multipoint index operator")
    {
        auto points = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
        auto p1 = points[0];
        auto p2 = points[1];
        CHECK(p1.x == 1.0);
        CHECK(p1.y == 2.0);
        CHECK(p2.x == 3.0);
        CHECK(p2.y == 4.0);
    }

    SECTION("3d multipoint index operator")
    {
        auto points = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
        auto p1 = points[0];
        auto p2 = points[1];
        auto p3 = points[2];
        CHECK(p1.x == 1.0);
        CHECK(p1.y == 2.0);
        CHECK(p2.x == 3.0);
        CHECK(p2.y == 4.0);
        CHECK(p3.x == 5.0);
        CHECK(p3.y == 6.0);
    }
}
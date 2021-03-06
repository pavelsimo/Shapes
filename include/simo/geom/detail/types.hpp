#pragma once

namespace simo
{
namespace shapes
{

/*!
 * @brief Geometry dimension type is (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
 *
 * @since 0.0.1
 */
enum class dimension_type : uint8_t
{
    XY   = 1,
    XYZ  = 2,
    XYM  = 3,
    XYZM = 4
};

/*!
 * @brief Element type for the geometry
 *
 * @since 0.0.1
 */
enum class element_type : uint8_t
{
    POINT      = 1,
    LINESTRING = 2,
    POLYGON    = 3
};

/*!
 * @brief Geometry types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
 *
 * @since 0.0.1
 */
enum class geometry_type : uint16_t
{
    GEOMETRY             = 0,
    POINT                = 1,
    LINESTRING           = 2,
    POLYGON              = 3,
    MULTIPOINT           = 4,
    MULTILINESTRING      = 5,
    MULTIPOLYGON         = 6,
    GEOMETRYCOLLECTION   = 7,
    CIRCULARSTRING       = 8,
    COMPOUNDCURVE        = 9,
    CURVEPOLYGON         = 10,
    MULTICURVE           = 11,
    MULTISURFACE         = 12,
    CURVE                = 13,
    SURFACE              = 14,
    POLYHEDRALSURFACE    = 15,
    TIN                  = 16,
    GEOMETRYZ            = 1000,
    POINTZ               = 1001,
    LINESTRINGZ          = 1002,
    POLYGONZ             = 1003,
    MULTIPOINTZ          = 1004,
    MULTILINESTRINGZ     = 1005,
    MULTIPOLYGONZ        = 1006,
    GEOMETRYCOLLECTIONZ  = 1007,
    CIRCULARSTRINGZ      = 1008,
    COMPOUNDCURVEZ       = 1009,
    CURVEPOLYGONZ        = 1010,
    MULTICURVEZ          = 1011,
    MULTISURFACEZ        = 1012,
    CURVEZ               = 1013,
    SURFACEZ             = 1014,
    POLYHEDRALSURFACEZ   = 1015,
    TINZ                 = 1016,
    GEOMETRYM            = 2000,
    POINTM               = 2001,
    LINESTRINGM          = 2002,
    POLYGONM             = 2003,
    MULTIPOINTM          = 2004,
    MULTILINESTRINGM     = 2005,
    MULTIPOLYGONM        = 2006,
    GEOMETRYCOLLECTIONM  = 2007,
    CIRCULARSTRINGM      = 2008,
    COMPOUNDCURVEM       = 2009,
    CURVEPOLYGONM        = 2010,
    MULTICURVEM          = 2011,
    MULTISURFACEM        = 2012,
    CURVEM               = 2013,
    SURFACEM             = 2014,
    POLYHEDRALSURFACEM   = 2015,
    TINM                 = 2016,
    GEOMETRYZM           = 3000,
    POINTZM              = 3001,
    LINESTRINGZM         = 3002,
    POLYGONZM            = 3003,
    MULTIPOINTZM         = 3004,
    MULTILINESTRINGZM    = 3005,
    MULTIPOLYGONZM       = 3006,
    GEOMETRYCOLLECTIONZM = 3007,
    CIRCULARSTRINGZM     = 3008,
    COMPOUNDCURVEZM      = 3009,
    CURVEPOLYGONZM       = 3010,
    MULTICURVEZM         = 3011,
    MULTISURFACEZM       = 3012,
    CURVEZM              = 3013,
    SURFACEZM            = 3014,
    POLYHEDRALSURFACEZM  = 3015,
    TINZM                = 3016
};

}  // namespace shapes
}  // namespace simo
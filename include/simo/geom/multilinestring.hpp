#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/sequence.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief A LineString collection
 *
 * @ingroup geometry
 *
 * @since 0.0.1
 */
class MultiLineString : public BaseGeometry<MultiLineString>, public detail::GeometrySequence<LineString>
{
  public:
    /*!
     * @brief Creates an empty MultiLineString
     *
     * @since 0.0.1
     */
    MultiLineString() = default;

    /*!
     * @brief Creates a MultiLineString from a given a LineString initializer list
     *
     * @param init the initializer list
     *
     * @since 0.0.1
     */
    MultiLineString(std::initializer_list<LineString> init)
    {
        if (init.size() > 0)
        {
            const auto& head = *init.begin();
            dim              = head.dim;
            seq.reserve(init.size());
            for (auto it = init.begin(); it != init.end(); ++it)
            {
                const auto& l = *it;
                if (l.dim != dim)
                {
                    throw exceptions::GeometryError("dimension mismatch at index " + std::to_string(it - init.begin()));
                }
                bounds.extend(l.bounds.minx, l.bounds.miny);
                bounds.extend(l.bounds.maxx, l.bounds.maxy);
                seq.push_back(l);
            }
        }
    }

    /*!
     * @brief Creates a MultiLineString from a given LineString vector
     *
     * @param linestrings the LineString vector
     *
     * @since 0.0.1
     */
    explicit MultiLineString(const std::vector<LineString>& linestrings)
    {
        if (not linestrings.empty())
        {
            seq = linestrings;
            dim = linestrings[0].dim;
            for (auto it = linestrings.begin(); it != linestrings.end(); ++it)
            {
                const auto& linestring = *it;
                if (linestring.dim != dim)
                {
                    throw exceptions::GeometryError("dimension mismatch at index " + std::to_string(it - linestrings.begin()));
                }
                bounds.extend(linestring.bounds.minx, linestring.bounds.miny);
                bounds.extend(linestring.bounds.maxx, linestring.bounds.maxy);
            }
        }
    }

    /*!
     * @brief Creates a MultiLineString from two pair of iterators
     *
     * @tparam CoordInputIt the coordinate input iterator
     * @tparam OffsetInputIt the offset input iterator
     * @param coord_first the first coordinate iterator
     * @param coord_last the second coordinate iterator
     * @param offset_first the offset first iterator
     * @param offset_last the offset last iterator
     * @param input_dim the dimension type
     *
     * @since 0.0.1
     */
    template <typename CoordInputIt, typename OffsetInputIt>
    MultiLineString(CoordInputIt coord_first, CoordInputIt coord_last, OffsetInputIt offset_first, OffsetInputIt offset_last, DimensionType input_dim)
    {
        dim = input_dim;
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto ndim = static_cast<size_t>(utils::get_ndim(input_dim));
            seq.reserve((coord_last - coord_first) / ndim);
            size_t lo = 0;
            for (auto it = offset_first; it != offset_last; ++it)
            {
                size_t hi = *it;
                seq.emplace_back(coord_first + lo, coord_first + hi, input_dim);
                lo            = hi;
                const auto& l = seq[seq.size() - 1];
                bounds.extend(l.bounds.minx, l.bounds.miny);
                bounds.extend(l.bounds.maxx, l.bounds.maxy);
            }
        }
    }

    /*!
     * @brief Creates a MultiLineString from a geojson string
     *
     * @param json the geojson string
     * @return a MultiLineString object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static MultiLineString from_json(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "MultiLineString")
            {
                throw exceptions::ParseError("invalid geometry type: " + std::string(geom_type));
            }
            const auto& linestrings = j.at("coordinates");
            std::vector<LineString> res;
            res.reserve(linestrings.size());
            std::vector<Point> points;
            for (const auto& linestring : linestrings)
            {
                if (not linestring.empty())
                {
                    const auto& coords = linestring.get<std::vector<std::vector<double>>>();
                    points.reserve(coords.size());
                    std::for_each(std::begin(coords), std::end(coords), [&points](const std::vector<double>& coord) {
                        points.emplace_back(coord);
                    });
                    res.emplace_back(points);
                }
                points.clear();
            }
            return MultiLineString(res);
        }
        catch (const nlohmann::json::exception& e)
        {
            throw exceptions::ParseError("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::GeometryError& e)
        {
            throw exceptions::ParseError("invalid geometry: " + std::string(e.what()));
        }
    }

    /*!
     * @brief Dumps the geojson representation of the MultiLineString
     *
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "{\"type\":\"MultiLineString\",\"coordinates\":[";
        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            const auto& linestring = seq.at(i);
            for (size_t j = 0; j < linestring.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                const auto& p = linestring.at(j);
                switch (p.dim)
                {
                    case DimensionType::XY:
                    {
                        ss << "[" << p.x << "," << p.y << "]";
                        break;
                    }
                    case DimensionType::XYZ:
                    {
                        ss << "[" << p.x << "," << p.y << "," << p.z << "]";
                        break;
                    }
                    case DimensionType::XYM:
                    {
                        ss << "[" << p.x << "," << p.y << "," << p.m << "]";
                        break;
                    }
                    case DimensionType::XYZM:
                    {
                        ss << "[" << p.x << "," << p.y << "," << p.z << "," << p.m << "]";
                        break;
                    }
                }
            }
            ss << "]";
        }
        ss << "]}";
        return ss.str();
    }

    /*!
     * @brief Creates a MultiLineString from a WKT string
     *
     * @param wkt the WKT string
     * @return a MultiLineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static MultiLineString from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multilinestring(data.geom_type))
        {
            throw exceptions::ParseError("invalid wkt string");
        }
        return {data.coords.begin(), data.coords.end(), data.offsets.begin(), data.offsets.end(), utils::get_dim(data.geom_type)};
    }

    /*!
     * @brief Creates a MultiLineString from a WKT string
     *
     * @param wkt the WKT string
     * @return a MultiLineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "MULTILINESTRING";
        if (has_z())
        {
            ss << "Z";
        }
        if (has_m())
        {
            ss << "M";
        }
        ss << "(";
        for (size_t i = 0; i < seq.size(); ++i)
        {
            const auto& linestring = seq.at(i);
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(";
            for (size_t j = 0; j < linestring.size(); ++j)
            {
                const auto& p = linestring.at(j);
                if (j > 0)
                {
                    ss << ",";
                }
                ss << p.x << " " << p.y;
                if (has_z())
                {
                    ss << " " << p.z;
                }
                if (has_m())
                {
                    ss << " " << p.m;
                }
            }
            ss << ")";
        }
        ss << ")";
        return ss.str();
    }

    /*!
     * @brief Creates a MultiLineString from a polyline string
     *
     * @param polyline the polyline string
     * @return a MultiLineString object
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static MultiLineString from_polyline(const std::vector<std::string>& polylines)
    {
        std::vector<LineString> res;
        res.reserve(polylines.size());
        for (const auto& polyline : polylines)
        {
            res.emplace_back(polyline::decode(polyline), DimensionType::XY);
        }
        return MultiLineString(res);
    }

    /*!
     * @brief Dumps the polyline representation of the MultiLineString
     *
     * @return a polyline string
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @since 0.0.1
     */
    std::vector<std::string> polyline()
    {
        std::vector<std::string> res;
        res.reserve(seq.size());
        std::for_each(seq.begin(), seq.end(), [&res](const LineString& ls) {
            res.push_back(ls.polyline());
        });
        return res;
    }

    /*!
     * @param lhs a MultiLinestring
     * @param rhs a MultiLinestring
     * @return true if all LineStrings are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const MultiLineString& lhs, const MultiLineString& rhs);

    /*!
     * @param lhs a MultiLinestring
     * @param rhs a MultiLinestring
     * @return true if at least one LineString is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const MultiLineString& lhs, const MultiLineString& rhs);

  private:
    /// for allow BaseGeometry to access MultiLineString private members
    friend class BaseGeometry<MultiLineString>;

    /// @private
    GeometryType geom_type_() const
    {
        return GeometryType::MULTILINESTRING;
    }

    /// @private
    std::string geom_type_str_() const
    {
        return "MultiLineString";
    }

    /// @private
    std::vector<std::vector<double>> coords_() const
    {
        std::vector<std::vector<double>> res;
        res.reserve(seq.size());
        for (const auto& ls : seq)
        {
            std::for_each(std::begin(ls), std::end(ls), [&res](const Point& p) {
                res.push_back(std::move(p.coords()[0]));
            });
        }
        return res;
    }

    /// @private
    bool empty_() const
    {
        return seq.empty();
    }

    /// @private
    size_t size_() const
    {
        return seq.size();
    }

    /// @private
    size_t num_points() const
    {
        size_t n = 0;
        for (const auto& linestring : seq)
        {
            n += linestring.size();
        }
        return n;
    };

    /// @private
    bool is_closed_() const
    {
        throw exceptions::NotImplementedError();
    }
};

bool operator==(const MultiLineString& lhs, const MultiLineString& rhs)
{
    return detail::is_equal_sequence(lhs, rhs);
}

bool operator!=(const MultiLineString& lhs, const MultiLineString& rhs)
{
    return not operator==(lhs, rhs);
}

}  // namespace shapes
}  // namespace simo
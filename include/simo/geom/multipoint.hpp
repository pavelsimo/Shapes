#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/sequence.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief Point collection
 *
 * @ingroup geometry
 *
 * @since 0.0.1
 */
class MultiPoint : public BaseGeometry<MultiPoint>, public detail::GeometrySequence<Point>
{
  public:
    /*!
     * @brief Creates an empty MultiPoint
     *
     * @since 0.0.1
     */
    MultiPoint() = default;

    /*!
      * @brief Creates a MultiPoint from a given initializer list
      *
      * @tparam T an arithmetic value (e.g. int, float, double)
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(std::initializer_list<std::initializer_list<T>> init)
    {
        detail::create_sequence(init, seq, bounds, dim);
    }

    /*!
     * @brief Creates a MultiPoint from a given point vector
     *
     * @param points the Point sequence
     *
     * @since 0.0.1
     */
    explicit MultiPoint(const std::vector<Point>& points)
    {
        detail::create_sequence(points, seq, bounds, dim);
    }

    /*!
     * @brief Creates a MultiPoint from a given arithmetic value sequence
     *
     * @tparam T an arithmetic value (e.g. int, float, double)
     * @param coords the arithmetic value sequence
     * @param coords_dim the dimension of the points
     *
     * @since 0.0.1
     */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(const std::vector<T>& coords, DimensionType coords_dim)
    {
        detail::create_sequence(coords, coords_dim, seq, bounds, dim);
    }

    /*!
     * @brief Creates a MultiPoint from a geojson string
     *
     * @param json the geojson string
     * @return a MultiPoint object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static MultiPoint from_json(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "MultiPoint")
            {
                throw exceptions::ParseError("invalid geometry type: " + std::string(geom_type));
            }
            const auto& coords = j.at("coordinates").get<std::vector<std::vector<double>>>();
            std::vector<Point> res;
            res.reserve(coords.size());
            std::for_each(std::begin(coords), std::end(coords), [&](const std::vector<double>& coord) {
                res.emplace_back(coord);
            });
            return MultiPoint(res);
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
     * @brief Dumps the geojson representation of the MultiPoint
     *
     * @param precision the output precision
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json(std::int32_t precision = -1)
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"MultiPoint\",\"coordinates\":[";
        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            const auto& p = seq[i];
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
        ss << "]}";
        return ss.str();
    }

    /*!
     * @brief Creates a MultiPoint from a WKT string
     *
     * @param wkt the WKT string
     * @return a MultiPoint object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static MultiPoint from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multipoint(data.geom_type))
        {
            throw exceptions::ParseError("invalid wkt string");
        }
        auto dim = utils::get_dim(data.geom_type);
        return MultiPoint(result.data.coords, dim);
    }

    /*!
     * @brief Dumps the WKT representation of the MultiPoint
     *
     * @param precision the output precision
     * @return a WKT string
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt(std::int32_t precision = -1)
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTIPOINT";
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
            const Point& p = seq[i];
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(" << p.x << " " << p.y;
            if (has_z())
            {
                ss << " " << p.z;
            }
            if (has_m())
            {
                ss << " " << p.m;
            }
            ss << ")";
        }
        ss << ")";
        return ss.str();
    }

    /*!
     * @brief Creates a MultiPoint from a polyline string
     *
     * @param polyline the polyline string
     * @return a MultiPoint object
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static MultiPoint from_polyline(const std::string& polyline)
    {
        /// @todo (pavel) add precision
        auto coords = polyline::decode(polyline);
        return {coords, DimensionType::XY};
    }

    /*!
     * @brief Dumps the polyline representation of the MultiPoint
     *
     * @return a polyline string
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @since 0.0.1
     */
    std::string polyline()
    {
        std::string res;
        res.reserve(seq.size() * 4);
        double prev_x = 0;
        double prev_y = 0;
        for (const auto& p : seq)
        {
            res += polyline::encode(p.y - prev_y);
            res += polyline::encode(p.x - prev_x);
            prev_x = p.x;
            prev_y = p.y;
        }
        return res;
    }

    /*!
     * @param lhs a MultiPoint
     * @param rhs a MultiPoint
     * @return true if all Point's are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const MultiPoint& lhs, const MultiPoint& rhs);

    /*!
     * @param lhs a MultiPoint
     * @param rhs a MultiPoint
     * @return true if at least one Point is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const MultiPoint& lhs, const MultiPoint& rhs);

  private:
    /// for allow BaseGeometry to access MultiPoint private members
    friend class BaseGeometry<MultiPoint>;

    /// @private
    GeometryType geom_type_() const
    {
        return GeometryType::MULTIPOINT;
    }

    /// @private
    std::string geom_type_str_() const
    {
        return "MultiPoint";
    }

    /// @private
    std::vector<std::vector<double>> coords_() const
    {
        std::vector<std::vector<double>> res;
        res.reserve(seq.size());
        std::for_each(std::begin(seq), std::end(seq), [&res](const Point& p) {
            res.push_back(std::move(p.coords()[0]));
        });
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
    bool is_closed_() const
    {
        if (seq.size() < 2)
        {
            return false;
        }
        size_t last_index = seq.size() - 1;
        return seq[0] == seq[last_index];
    }
};

bool operator==(const MultiPoint& lhs, const MultiPoint& rhs)
{
    return detail::is_equal_sequence(lhs, rhs);
}

bool operator!=(const MultiPoint& lhs, const MultiPoint& rhs)
{
    return not operator==(lhs, rhs);
}

}  // namespace shapes
}  // namespace simo
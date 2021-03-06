#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <simo/geom/detail/geometry.hpp>
#include <simo/geom/detail/bounds.hpp>

namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_multilinestring
    : public std::vector<T, AllocatorType>,
      public basic_geometry<basic_multilinestring<T>>
{
  public:
    using base_type            = std::vector<T, AllocatorType>;
    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<T>::iterator;
    using point_const_iterator = typename std::vector<T>::const_iterator;
    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_multilinestring()
        : base_type() {}

    basic_multilinestring(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    basic_multilinestring(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    basic_multilinestring(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    template <typename CoordIterator, typename OffsetIterator>
    basic_multilinestring(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto n = this->ndim();
            this->reserve((coord_last - coord_first) / n);
            size_t lo = 0;
            for (auto it = offset_first; it != offset_last; ++it)
            {
                size_t hi = *it;
                this->emplace_back(coord_first + lo, coord_first + hi);
                lo = hi;
            }
        }
    }

    // operators

    friend bool operator==(const basic_multilinestring<T>& lhs, const basic_multilinestring<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const basic_multilinestring<T>& lhs, const basic_multilinestring<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

  private:
    /// for allow basic_geometry to access basic_multipoint private members
    friend class basic_geometry<basic_multilinestring<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_linestring_z<T>::value)
        {
            return geometry_type::MULTILINESTRINGZ;
        }
        if (is_basic_linestring_m<T>::value)
        {
            return geometry_type::MULTILINESTRINGM;
        }
        if (is_basic_linestring_zm<T>::value)
        {
            return geometry_type::MULTILINESTRINGZM;
        }
        return geometry_type::MULTILINESTRING;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        return *this[0] == *this[this->size() - 1];
    }

    /// @private
    void throw_for_invalid_() const
    {
        for (const auto& ls : *this)
        {
            ls.throw_for_invalid();
        }
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& p : *this)
        {
            res.extend(p.x, p.y);
        }
        return res;
    }

    // json

    /// @private
    static basic_multilinestring<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "MultiLineString")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& linestrings = j.at("coordinates");
            std::vector<T> res;
            res.reserve(linestrings.size());
            std::vector<point_type> points;
            for (const auto& linestring : linestrings)
            {
                if (not linestring.empty())
                {
                    const auto& coords = linestring.get<std::vector<std::vector<double>>>();
                    points.reserve(coords.size());
                    std::for_each(std::begin(coords), std::end(coords),
                                  [&points](const std::vector<double>& coord) {
                                      points.emplace_back(coord.begin(), coord.end());
                                  });
                    res.emplace_back(points.begin(), points.end());
                }
                points.clear();
            }
            return basic_multilinestring<T>(res.begin(), res.end());
        }
        catch (const nlohmann::json::exception& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"MultiLineString\",\"coordinates\":[";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << "[";
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        ss << ",";
                    }
                    ss << p.coords[k];
                }
                ss << "]";
                ++i;
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_multilinestring<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multilinestring(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_multilinestring<T>(result.data.coords.begin(), result.data.coords.end(),
                                        result.data.offsets.begin(), result.data.offsets.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTILINESTRING";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        ss << "(";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        ss << " ";
                    }
                    ss << p.coords[k];
                }
            }
            ss << ")";
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_multilinestring : std::false_type
{};

template <typename T>
struct is_basic_multilinestring<basic_multilinestring<basic_linestring<basic_point<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multilinestring_z : std::false_type
{};

template <typename T>
struct is_basic_multilinestring_z<basic_multilinestring<basic_linestring<basic_point_z<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multilinestring_m : std::false_type
{};

template <typename T>
struct is_basic_multilinestring_m<basic_multilinestring<basic_linestring<basic_point_m<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multilinestring_zm : std::false_type
{};

template <typename T>
struct is_basic_multilinestring_zm<basic_multilinestring<basic_linestring<basic_point_zm<T>>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo
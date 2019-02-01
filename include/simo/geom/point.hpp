#pragma once

#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <json/json.hpp>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>

namespace simo
{
namespace shapes
{

class Point : public Geometry<Point>
{
  public:
    double x;
    double y;
    double z;

    Point()
    {
        this->x      = 0;
        this->y      = 0;
        this->z      = 0;
        this->m_ndim = 2;
    }

    Point(double x, double y)
    {
        this->x      = x;
        this->y      = y;
        this->z      = 0;
        this->m_ndim = 2;
    }

    Point(double x, double y, double z)
    {
        this->x      = x;
        this->y      = y;
        this->z      = z;
        this->m_ndim = 3;
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Point(std::initializer_list<T> init)
    {
        if (init.size() == 2)
        {
            this->x      = *init.begin();
            this->y      = *(init.begin() + 1);
            this->z      = 0;
            this->m_ndim = 2;
        }
        else if (init.size() == 3)
        {
            this->x      = *init.begin();
            this->y      = *(init.begin() + 1);
            this->z      = *(init.begin() + 2);
            this->m_ndim = 3;
        }
        else
        {
            throw exception();
        }
    }

    GeometryType geom_type_impl() const
    {
        return GeometryType::POINT;
    }

    std::string geom_type_str_impl() const
    {
        return "Point";
    }

    int8_t dimension_impl() const
    {
        return m_ndim;
    }

    bool empty_impl() const
    {
        return false;
    }

    double at(size_t pos)
    {
        if (pos >= size_impl())
        {
            throw exception();
        }
        if (pos == 0)
            return x;
        if (pos == 1)
            return y;
        return z;
    }

    double operator[](size_t pos)
    {
        return at(pos);
    }

    size_t size_impl() const
    {
        return static_cast<size_t>(m_ndim);
    }

    std::tuple<double, double> xy() const
    {
        return std::make_tuple(x, y);
    }

    std::tuple<double, double, double> xyz() const
    {
        return std::make_tuple(x, y, z);
    }

    static Point from_json(const std::string& json)
    {
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "Point")
        {
            throw parse_error();
        }

        std::vector<double> coords = j.at("coordinates");
        if (coords.size() == 2)
        {
            return {coords[0], coords[1]};
        }
        else if (coords.size() == 3)
        {
            return {coords[0], coords[1], coords[2]};
        }

        throw parse_error();
    }

    std::string to_json()
    {
        auto coordinates = std::vector<double>{x, y};
        if (m_ndim == 3)
        {
            coordinates.push_back(z);
        }
        nlohmann::json j = {{"type", "Point"}, {"coordinates", coordinates}};
        return j.dump();
    }

  private:
    int8_t m_ndim;
};

}  // namespace shapes
}  // namespace simo
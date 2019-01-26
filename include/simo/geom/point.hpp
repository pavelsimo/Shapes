#pragma once

#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <string>
#include <type_traits>
#include <json/json.hpp>
#include <simo/geom/geometry.hpp>

namespace simo
{
namespace shapes
{

class point_t
{
  public:
    double x;
    double y;
    double z;

    point_t()
    {
        this->x           = 0;
        this->y           = 0;
        this->z           = 0;
        this->m_dimension = 2;
    }

    template <
        typename T,  // integer,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    point_t(std::initializer_list<T> list)
    {
        if (list.size() == 2)
        {
            this->x           = *list.begin();
            this->y           = *(list.begin() + 1);
            this->z           = 0;
            this->m_dimension = 2;
        }
        else if (list.size() == 3)
        {
            this->x           = *list.begin();
            this->y           = *(list.begin() + 1);
            this->z           = *(list.begin() + 2);
            this->m_dimension = 3;
        }
        else
        {
            /// @todo (pavel) report error
        }
    }

    GeometryType geom_type() const
    {
        return GeometryType::POINT;
    }

    std::string geom_type_str() const
    {
        return "POINT";
    }

    int8_t dimension() const
    {
        return m_dimension;
    }

    static point_t from_json(const std::string& json)
    {
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "Point")
        {
            // parse error
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

        /// @todo thrown an exception
        return {};
    }

    std::string to_json()
    {
        std::vector<double> coords = {x, y};
        if (m_dimension == 3)
        {
            coords.push_back(z);
        }
        nlohmann::json j = {{"type", "Point"}, {"coordinates", coords}};
        return j.dump();
    }

  private:
    int8_t m_dimension;
};

typedef Geometry<point_t> Point;

}  // namespace shapes
}  // namespace simo
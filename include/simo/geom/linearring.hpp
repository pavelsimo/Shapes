#pragma once

#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/point_collection.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

class LinearRing : public BasicGeometry<LinearRing>, public PointCollection<LinearRing>
{
  public:
    /// two-dimensional rotation direction, clockwise=true, counterclockwise=false
    bool clockwise = true;

    /*!
     * @brief creates an empty LinearRing
     *
     * @since 0.0.1
     */
    LinearRing() = default;

    /*!
      * @brief creates a LinearRing from a given initializer list
      *
      * @tparam T an arithmetic value (e.g. int, float, double)
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    LinearRing(std::initializer_list<std::initializer_list<T>> init)
    {
        m_points.reserve(init.size());
        Bounds& b = bounds();
        for (const auto& coords : init)
        {
            Point p(coords);
            b.extend(p.x, p.y);
            m_points.emplace_back(std::move(p));
        }
        valid_or_throw();
    }

    /*!
     * @brief creates a LinearRing from a given point vector
     *
     * @param points the point list
     * @param validate whether to validate the geometry
     *
     * @since 0.0.1
     */
    explicit LinearRing(const std::vector<Point>& points)
    {
        m_points  = points;
        Bounds& b = bounds();
        for (const auto& p : m_points)
        {
            b.extend(p.x, p.y);
        }
        valid_or_throw();
    }

    /// @private
    GeometryType type_() const
    {
        return GeometryType::LINESTRING;
    }

    /// @private
    std::string type_str_() const
    {
        return "LineString";
    }

  private:
    void valid_or_throw() const
    {
        if (empty())
        {
            return;
        }

        if (m_points.size() < 4)
        {
            throw exceptions::value_error("LinearRing should be either empty or with 4 or more points");
        }

        if (not is_closed())
        {
            throw exceptions::value_error("LinearRing is not closed, first and last point are different");
        }

        /// @todo (pavel) check for self-intersections
    }
};

}  // namespace shapes
}  // namespace simo
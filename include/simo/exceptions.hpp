#pragma once

#include <ciso646>
#include <string>
#include <exception>

namespace simo
{
namespace shapes
{
namespace exceptions
{

/*!
 * @brief Base shapes exception
 *
 * @since 0.0.1
 */
class shapes_exception : public std::exception
{
  public:
    /*!
     * @brief Creates a shapes exception
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit shapes_exception(const char* reason)
        : m_reason(reason) {}

    /*!
     * @brief Returns the exception reason
     *
     * @return a string with the exception reason
     *
     * @since 0.0.1
     */
    const char* what() const noexcept override
    {
        return m_reason.c_str();
    }

  protected:
    /*!
     * @brief Set the exception reason
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    void set_reason(const std::string& reason)
    {
        m_reason.append(": ");
        m_reason.append(reason);
    }

  private:
    std::string m_reason{};
};

/*!
 * @brief Exception thrown when an error has been found while parsing
 *
 * @since 0.0.1
 */
class parse_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a parse error with the given reason
     *
     * @param reason the reason message
     *
     * @since 0.0.1
     */
    explicit parse_error(const std::string& reason)
        : shapes_exception("parse error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief Exception thrown when method or routine is not implemented
 *
 * @since 0.0.1
 */
class not_implemented_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a not implemented error exception
     *
     * @since 0.0.1
     */
    not_implemented_error()
        : shapes_exception("not implemented error")
    {
    }

    /*!
     * @brief Creates a not implemented error exception
     *
     * @param reason the reason message
     *
     * @since 0.0.1
     */
    explicit not_implemented_error(const std::string& reason)
        : shapes_exception("not implemented error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief Exception thrown when a geometry error is found
 *
 * @since 0.0.1
 */
class geometry_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a geometry error exception
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit geometry_error(const std::string& reason)
        : shapes_exception("geometry error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief Exception thrown when a sequence index is out of range
 *
 * @since 0.0.1
 */
class index_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a index error exception
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit index_error(const std::string& reason)
        : shapes_exception("index error")
    {
        set_reason(reason);
    }
};

}  // namespace exceptions
}  // namespace shapes
}  // namespace simo

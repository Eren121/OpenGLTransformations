#include "Exception.hpp"
#include <sstream>

Exception::Exception(const std::string& msg, const nostd::source_location& location)
    : m_location(location)
{
    std::ostringstream ss;
    ss << location << ": ";
    ss << msg;

    m_message = ss.str();
}

const nostd::source_location& Exception::getLocation() const
{
    return m_location;
}

const char *Exception::what() const noexcept
{
    return m_message.c_str();
}

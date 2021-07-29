#include "Str.hpp"

Str::operator std::string() const
{
    return str();
}

std::string Str::str() const
{
    return m_stream.str();
}

std::string Str::operator<<(const Str::end_t&) const
{
    return str();
}

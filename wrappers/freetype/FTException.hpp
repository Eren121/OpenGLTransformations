#pragma once

#include <utility/Exception.hpp>

/// @brief Exception to throw for FreeType errors.
class FTException : public ::Exception
{
public:
    explicit FTException(int ft_error, const std::string& msg = "", const nostd::source_location& loc = nostd::source_location::current());
};

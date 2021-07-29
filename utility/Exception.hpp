#pragma once

#include "wrappers/nostd/source_location.hpp"
#include <stdexcept>

/// @brief Exception class but with source file, number and function name information.
class Exception : public virtual std::exception
{
public:
    Exception(const std::string& msg = "", const nostd::source_location& location = nostd::source_location::current());
    [[nodiscard]] const nostd::source_location& getLocation() const;
    const char *what() const noexcept override;

private:
    std::string m_message;
    nostd::source_location m_location;
};


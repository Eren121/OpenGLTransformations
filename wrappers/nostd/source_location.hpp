#pragma once

/// @dir
/// @brief Wrapper around C++20 components.
/// @details More easely maintenable in case of compiler-specific options and changes until full support.

#include <experimental/source_location>
#include <ostream>

#define SOURCE_LOCATION_DECL(arg) const nostd::source_location& arg = nostd::source_location::current()

namespace nostd
{
    using source_location = std::experimental::source_location;
}

/// @brief Overload to print a source_location.
/// @details The form is file.cpp(line:column) `function`
/// @remarks This function is non-standard.
std::ostream& operator<<(std::ostream& lhs, const nostd::source_location& rhs);
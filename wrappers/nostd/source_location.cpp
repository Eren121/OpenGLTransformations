#include "source_location.hpp"

std::ostream& operator<<(std::ostream& lhs, const nostd::source_location& rhs)
{
    lhs << rhs.file_name() << "(" << rhs.line() << ":" << rhs.column() << ")";
    lhs << " `" << rhs.function_name() << "`";

    return lhs;
}
#pragma once

#include "Exception.hpp"
#include <string>
#include <filesystem>

/// @brief Exception thrown if there is an error with IO functions.
class IOException : public Exception
{
public:
    using Exception::Exception;
};

class FileNotFoundException : public IOException
{
public:
    FileNotFoundException(const std::filesystem::path& path, SOURCE_LOCATION_DECL(location));
};

/// @brief I/O utility functions.
namespace IO
{
    /// @brief Read all the content of a file into a string.
    std::string readAll(const std::filesystem::path& path);
}
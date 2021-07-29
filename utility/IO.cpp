#include "IO.hpp"
#include "Str.hpp"
#include <fstream>

std::string IO::readAll(const std::filesystem::path& path)
{
    if(!std::filesystem::is_regular_file(path))
    {
        throw FileNotFoundException(path);
    }

    std::ifstream ifs(path.string());
    std::string str((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());

    return str;
}

FileNotFoundException::FileNotFoundException(const std::filesystem::path& path, const nostd::source_location& location)
    : IOException(Str{} << "File not found: " << std::filesystem::absolute(path), location)
{

}

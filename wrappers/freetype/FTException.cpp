#include "FTException.hpp"
#include <utility/Str.hpp>
#include <ft2build.h>
#include <map>
#include <string>
#include FT_FREETYPE_H

// Include & define macro, FreeType does not define errors by default to save space
// Since it need to be sure it was compiled with error enabled, we can still get the errors manually
// see https://www.freetype.org/freetype2/docs/reference/ft2-error_enumerations.html

namespace
{
    const std::string& getFreetypeError(int code)
    {
        // Error Code to error message string
        using ErrorMap = std::map<int, std::string>;

        static bool first = true;
        static ErrorMap messages;

        if(first)
        {
            first = false;
#undef FTERRORS_H_
#define FT_ERRORDEF( e, v, s )  messages[e] = s;
#define FT_ERROR_START_LIST
#define FT_ERROR_END_LIST
#include <freetype/fterrors.h>
        }

        return messages[code];
    }
}

FTException::FTException(int ft_error, const std::string& msg, const nostd::source_location& loc)
    : Exception(Str{} << "FreeType error: " << msg << ": (" << ft_error << ") " << getFreetypeError(ft_error), loc)
{

}

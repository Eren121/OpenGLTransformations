#pragma once

#include <sstream>

/// @brief Facilitate the use of simple formated inline strings.
/// @remarks For more complicated strings, use {fmt}.
/// @example
///     std::string a = "1 is a number";
///     std::string b = Str{} << 1 << " is a number".
///     // a == b
class Str
{
public:
    /// @brief Convert the Str to a std::string. Same as str().
    /// @remarks Non-explicit to allow automatic conversions.
    operator std::string() const;

    /// @brief Convert explicitly the Str to a std::string (if implicit conversion seems too dangerous).
    [[nodiscard]] std::string str() const;

private:
    /// @brief Tag class for Str::end. Ensure the class is not used anywhere else.
    struct end_t {};

public:
    /// @brief Tag class instance for operator<<().
    static inline constexpr end_t end {};

    /// @brief Overload of operator<<() to automatically convert to Str to a std::string.
    /// @details
    ///     It is because it is much simpler to use this than wrap the string around parenthesis and call str().
    ///     In some cases, implicit conversion doesn't work, for example giving a Str as an argument taking a type that
    ///     has an std::string constructor (C++ doesn't make indirect conversions).
    /// @example
    ///     <code>
    ///         std::string a = (Str{} << 1 << " hi").str(); // Possible, but tedious
    ///         std::string b = Str{} << 1 << " hi" << Str::end; // Much cleaer and simpler, no need for parenthesis.
    ///         // a == b
    ///     </code>
    [[nodiscard]] std::string operator<<(const end_t&) const;

    /// @brief Append any value to the string.
    template<typename T>
        requires (!std::is_same_v<T, end_t>)
    Str& operator<<(const T& str)
    {
        m_stream << str;
        return *this;
    }

private:
    std::ostringstream m_stream;
};
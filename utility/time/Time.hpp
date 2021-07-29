#pragma once

#include <chrono>
#include <iosfwd>

/// @brief Simple wrapper around std::chrono, because this API is a bit verbose and complicated...
/// @remarks Like sf::Time
class Time
{
public:
    /// @brief Construct a Time representing Zero.
    Time();

    /// @brief Get the elapsed time since an arbitrary origin, constant during all the program.
    static Time now();

    /// @name
    /// @brief Static factories to construct Time value from different units.
    /// @details The Time will contains the desired amount of time.
    /// @{

    static Time seconds(float amount);
    static Time milliseconds(uint32_t amount);

    /// @}

    /// @name
    /// @brief Convert the Time to an actual float or integral value.
    /// @{

    float asSeconds() const;
    uint32_t asMilliseconds() const;

    /// @}

    /// @name
    /// @brief Time arithmetic
    /// @{
    Time operator-(const Time& rhs) const;
    Time& operator-=(const Time& rhs);

    Time operator+(const Time& rhs) const;
    Time& operator+=(const Time& rhs);

    Time operator*(float f) const;
    Time& operator*=(float f);

    Time operator/(float f) const;
    Time& operator/=(float f);

    auto operator<=>(const Time& rhs) const = default;
    bool operator==(const Time& rhs) const = default;

    /// @}

private:
    using clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<clock>;

    /// @brief The stored type for duration
    /// @remarks We need a floating point to be able to multiply by float
    /// @remarks We also need a good precision, because if for example we are between two ms and the unit is ms,
    /// then it will be rounded which can lead to imprecision. Microsecond should be high enough and that is the unit
    /// used internally by the SFML.
    using duration = clock::duration;

    explicit Time(duration dur);

    /// @brief Internal representation of the time that this instance represents.
    /// @details Represent the time elapsed since the origin.
    duration m_duration;

    friend std::ostream& operator<<(std::ostream& lhs, const Time& rhs);

    /// @brief The time origin, representing zero.
    static const time_point origin;
};
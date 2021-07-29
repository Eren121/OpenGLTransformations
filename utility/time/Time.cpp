#include "Time.hpp"
#include <ostream>

const Time::time_point Time::origin = Time::clock::now();

Time::Time()
    : m_duration(duration::zero())
{
    // m_duration IS __NOT__ ZEROED DUE TO OPTIMIZATIONS!!!
    // Thanks to Valgrind, detected... We need to set to zero ourselves
}

Time::Time(duration duration)
    : m_duration(duration)
{
}

Time Time::now()
{
    auto currentTime = clock::now();
    auto dur = std::chrono::duration_cast<duration>(currentTime - origin);
    return Time{dur};
}

Time Time::seconds(float amount)
{
    auto dur = std::chrono::duration<float>(amount);
    return Time{std::chrono::duration_cast<duration>(dur)};
}

Time Time::milliseconds(uint32_t amount)
{
    auto dur = std::chrono::duration<uint32_t, std::milli>(amount);
    return Time{std::chrono::duration_cast<duration>(dur)};
}

float Time::asSeconds() const
{
    auto dur = std::chrono::duration_cast<std::chrono::duration<float>>(m_duration);
    return dur.count();
}

uint32_t Time::asMilliseconds() const
{
    auto dur = std::chrono::duration_cast<std::chrono::duration<uint32_t, std::milli>>(m_duration);
    return dur.count();
}

std::ostream& operator<<(std::ostream& lhs, const Time& rhs)
{
    lhs << rhs.asSeconds() << "s";
    return lhs;
}

Time Time::operator-(const Time& rhs) const
{
    return Time{m_duration - rhs.m_duration};
}

Time& Time::operator-=(const Time& rhs)
{
    m_duration -= rhs.m_duration;
    return *this;
}

Time Time::operator+(const Time& rhs) const
{
    return Time{m_duration + rhs.m_duration};
}

Time& Time::operator+=(const Time& rhs)
{
    m_duration += rhs.m_duration;
    return *this;
}

Time Time::operator*(float f) const
{
    auto dur = std::chrono::duration_cast<duration>(m_duration * f);
    return Time{dur};
}

Time& Time::operator*=(float f)
{
    // We can't use '*=' operator because it will convert f to decltype(duration.count())
    // Since by default STL use only integers type, f will be converted as an integer, resulting for example if f = 0.8,
    // converting to 0.
    // However we round the maximal precision, which should not be a problem because the precision is high enough.
    // (can't go in fractional duration, so the duration will probably be rounded to something like the micro or the nano).

    m_duration = std::chrono::duration_cast<duration>(m_duration * f);
    return *this;
}

Time Time::operator/(float f) const
{
    auto dur = std::chrono::duration_cast<duration>(m_duration / f);
    return Time{dur};
}

Time& Time::operator/=(float f)
{
    m_duration = std::chrono::duration_cast<duration>(m_duration / f);
    return *this;
}

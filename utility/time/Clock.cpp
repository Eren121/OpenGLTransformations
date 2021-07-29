#include "Clock.hpp"

Clock::Clock(bool initiallyPaused)
    : m_isPaused(initiallyPaused),
      m_speed(1.0f)
{
}

Time Clock::getElapsedTime() const
{
    if(m_isPaused)
    {
        // The clock is paused, we do not add the time since it is paused
        return m_accumulator;
    }
    else
    {
        // The clock is not paused, we add the time elapsed since the speed changed
        return m_accumulator + (Time::now() - m_lastSpeedChange) * m_speed;
    }
}

Time Clock::restart()
{
    // Returns the time elapsed (before resetting the clock...)
    Time elapsed = getElapsedTime();

    // Reset the accumulated time to Zero
    m_accumulator = {};

    // Reset the time point to now
    m_lastSpeedChange = Time::now();

    return elapsed;
}

void Clock::pause()
{
    const Time now = Time::now();

    // Do not do anything if it is already paused, paused need to update the internal state
    // Same with resume()

    if(!m_isPaused)
    {
        m_isPaused = true;

        // Update the accumulator
        m_accumulator += (now - m_lastSpeedChange) * m_speed;

        // Pause is changing the sequence of time
        // It is like setting the speed to 0.0f
        // We could do it be we do not it to not change and keep the user speed value.

        // We do not need to change the last speed change because we already updated the accumulator.
        // We only need to know when the Clock will be resumed(), and here it will be updated.
    }
}

void Clock::resume()
{
    if(m_isPaused)
    {
        m_isPaused = false;
        m_lastSpeedChange = Time::now();

        // Do not change the accumulator because the time in pause is ignored.
    }
}

bool Clock::isPaused() const
{
    return m_isPaused;
}

void Clock::setPaused(bool paused)
{
    if(paused)
    {
        pause();
    }
    else
    {
        resume();
    }
}

void Clock::toggle()
{
    setPaused(!m_isPaused);
}

float Clock::getSpeed() const
{
    return m_speed;
}

void Clock::setSpeed(float speed)
{
    if(m_speed != speed)
    {
        // If it is not paused, we need also to update the accumulator from the previous speed.
        // It is an easy way to do it.

        if(!m_isPaused)
        {
            const Time now = Time::now();
            m_accumulator += (now - m_lastSpeedChange) * m_speed;
            m_lastSpeedChange = now;
        }

        m_speed = speed;
    }
}

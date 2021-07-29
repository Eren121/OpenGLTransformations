#pragma once

#include "Time.hpp"

/// @brief Pausable and scalable sf::Clock.
/// @details
/// Same interface as sf::Clock in addition to two functionalities:
/// a pause() function and a setSpeed() function. The speed of the clock affects how the time is elapsed by it.
/// The base time is the real time, but for example if the speed is set to 0.5, then the clock will see time twice
/// as slow: when one real second will be elapsed, the clock's getElapsedTime() would return only 0.5s.
class Clock
{
public:
    /// @param initiallyPaused
    /// true, the Clock is not automatically started and you have to manually start it.
    /// false (by default), then the clock will measure elapsed time as soon as this constructor is called.
    Clock(bool initiallyPaused = false);

    /// @brief Get the elapsed time since the previous reset of the clock or since its creation.
    Time getElapsedTime() const;

    /// @remarks Do not change the pause flag. If the Clock is paused, then restarting it will not resume it.
    /// @returns The elapsed time before the restart.
    Time restart();

    /// @name
    /// @brief Pausable interface.
    /// @{
    void pause();
    void resume();

    /// @brief Resume if paused, or pause if not paused.
    void toggle();

    void setPaused(bool paused);
    bool isPaused() const;
    /// @}

    /// @brief Set the speed of the Clock.
    /// @details
    /// The speed defines how fast the Clock's time elapse. By default, the speed is 1.
    /// For example, a speed of 2 means when 1s is elapsed IRL, the Clock's getElapsedTime() will return 2s.
    /// The time will also elapse twice faster.
    /// @remarks It does not reset the elapsed time, but rather accumulates it.
    void setSpeed(float speed);

    /// @brief Get the speed of the Clock.
    float getSpeed() const;

private:
    /// @brief All accumulated elapsed time when unpaused.
    /// @remarks Do not contains the time of the current sequence if unpaused.
    Time m_accumulator;

    bool m_isPaused;

    /// @brief The real time point at which the last time the speed was changed.
    /// @details To manage the speed, we don't have to update and add a delta time, we can just manage
    /// 'sequence' of times. If we know the speed hasn't changed between two points, we can just take the difference
    /// and multiply by the speed. So, in fact, we just need to know the total accumulated time (in m_accumulator)
    /// and the last time the speed has changed, here.
    Time m_lastSpeedChange;

    /// @brief The speed of the Clock.
    /// @remarks One by default.
    float m_speed;
};
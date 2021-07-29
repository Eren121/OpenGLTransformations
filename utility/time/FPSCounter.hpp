#pragma once

#include "Clock.hpp"

/// @brief Count the FPS.
/// @remarks Stored as a time utility because the definition of 'frame' may be anything. Even if obviously the main
/// purpose is to count FPSes. It only measure how many times an unspecified event occured between two point of time,
/// and gives the average of events per second.
class FPSCounter
{
public:
    explicit FPSCounter(Time snapshot = Time::milliseconds(400));

    /// @brief Notify one frame
    void onFrame();

    /// @brief Get the fps measured. Do not change between two snapshots.
    float getFPS() const;

    /// @brief The duration of a snapshot.
    /// @details A snapshot is an interval of time in which we count the frames, to have a statistically accurate
    /// measure. Then, the fps is calculated as fps = framesPassed / snapshot.asSeconds().
    /// May be changed at any time.
    Time snapshot;

private:
    /// @brief If the snapshot ended, then we store the FPS and reset the timer.
    void reset();

    /// @brief Count of frames since the beginning of the snapshot.
    int m_count;

    /// @brief Measure the time elapsed since the beginning of the snapshot.
    Clock m_elapsed;

    /// @brief FPS count for the previous snapshot (cache).
    float m_fps;
};


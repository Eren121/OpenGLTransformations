
#include "FPSCounter.hpp"

FPSCounter::FPSCounter(Time snapshot)
    : snapshot(snapshot), m_count(0), m_elapsed(), m_fps(0.0f)
{
}

void FPSCounter::onFrame()
{
    m_count++;

    if(m_elapsed.getElapsedTime() > snapshot)
    {
        reset();
    }
}

float FPSCounter::getFPS() const
{
    return m_fps;
}

void FPSCounter::reset()
{
    m_fps = static_cast<float>(m_count) / m_elapsed.restart().asSeconds();
    m_count = 0;
}




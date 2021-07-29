#pragma once

#include <utility>

/// @brief
/// @details
/// Example:
///     void f() {
///         WhenLeaveScope {
///             cout << "Leaving f() function!"; // Same scope as enclosing scope, which is f()
///         };
///     }
/// @remarks
/// We know (as normal use in the example) that the guard will be destroyed after all captured variables,
/// because variables are destroyed in inverse order of declaration, so it is fine to capture everything by reference.
#define WhenLeaveScope2(line) Guard guardXXXXXXXXXX##line = [&]()
#define WhenLeaveScope WhenLeaveScope2(__LINE__)

/// @brief Generic RAII.
/// @details Executes code when this object is destructed.
template<typename T>
class Guard
{
public:
    Guard(T&& onDestruct)
        : m_onDestruct(std::forward<T>(onDestruct))
    {
    }

    ~Guard()
    {
        m_onDestruct();
    }

private:
    T m_onDestruct;
};


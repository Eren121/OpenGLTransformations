#pragma once

template<typename T, auto next>
concept list_iterator_free_next = requires(T *t) {
    t = next(t);
};

/// @brief Convert automatically some types to iterators.
/// @details
/// Box2D doesn't use STL container, but use for its objects a method object->GetNext() to iterate.
/// This class permit to iterate any pointer by providing the method to get the next element of the list based
/// on the current element.
/// Unless as a value representing the end iterator, nullptr is not permitted inside the sequence.
/// The returned type of the iterator is a reference and not a pointer as it is not permitted to store nullptr,
/// Example:
///     int* next(int *i) { ... }
///     void f()
///     {
///         int *i = ...
///         list_iterator<int, next> it(i);
///         int& iRef = *it;
///         assert(i == &iRef);
///     }
///
/// @tparam T The type stored. Store an object of type T*.
/// @tparam next
/// The callable to get the next value. Should return nullptr to mean the end of the list.
/// Default's to the member function GetNext, as Box2D members does.
/// Either one of these expression should be valid, for a variable t of type T*:
///     t = next(*t); // As a free function
///     t = t.(*next)(); // As a member function of T
/// @remarks We may need to cast the default next argument to disambiguate the const and non-const versions of the method.
/// If T is const, then we take the const overload. If T is non-const, then we take the non-const overload
template<typename T, auto next>
    requires
        list_iterator_free_next<T, next> ||
        requires(T* t) { t = (t->*next)(); }
class list_iterator
{
private:
    static constexpr bool isFreeFunc() // Verbose due to MSVC poor support
    {
        return list_iterator_free_next<T, next>;
    }

  /// @brief The current value pointed by this iterator. nullptr means this pointer is an end iterator.
    T *m_currentValue;

    /// @brief Get the next value, based on if next is either a member function or a free function.
    inline static T* getNext(T* current)
    {
        if constexpr(isFreeFunc())
        {
            return next(*current);
        }
        else
        {
            return (current->*next)();
        }
    }

public:
    /// @brief Constructor.
    /// @param currentValue The current value. nullptr means this is an end iterator.
    list_iterator(T *currentValue)
        : m_currentValue(currentValue)
    {
    }

    /// @brief Prefix increment operator.
    list_iterator& operator++()
    {
        m_currentValue = list_iterator::getNext(m_currentValue);
        return *this;
    }

    /// @brief Equality comparison operator.
    /// @param rhs The right-hand-side of the operation.
    bool operator==(const list_iterator& rhs) const
    {
        return rhs.m_currentValue == m_currentValue;
    }

    /// @name
    /// @brief Get the stored value. This iterator should not be an end iterator.
    /// @{

    /// @returns The dereferenced pointer stored by this iterator.
    T& operator*() const
    {
        return *m_currentValue;
    }

    /// @returns The stored value.
    T* operator->() const
    {
        return m_currentValue;
    }

    /// @}
};;

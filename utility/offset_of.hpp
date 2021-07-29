#pragma once

#include <cstddef>
#include <cstdint>

// Compile time compatible offsetof()
template<typename Class, typename FieldType>
std::uintptr_t offset_of(FieldType(Class::*field))
{
    const Class* ptr{nullptr};

    auto offset = reinterpret_cast<std::uintptr_t>(&(ptr->*field));
    return offset;
}
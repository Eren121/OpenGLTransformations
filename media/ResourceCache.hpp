#pragma once

#include <string>
#include <unordered_map>
#include <concepts>

/// @brief Resource concept (textures, sound, shaders, etc...).
/// @details Resources are objects that are used many times but will only be loaded once in the memory.
/// A resource should be default constructible.
template<typename T>
concept ResourceConcept = std::constructible_from<T>;

/// @brief Cache loader concept.
/// @brief A cache loader is in charge of loading the resource from it's ID.
template<typename T>
class ResourceLoader
{
public:
    virtual void loadResource(T& resource, const std::string& id) = 0;
};

/// @brief Cache for the resources
/// @details
/// It lazy loads, that means the asset is loaded the first time is it asked, like static local variables in C++.
/// Each asset has an identifier, the most simple case is to use the path of the asset as the identifier.
template<ResourceConcept T>
class ResourceCache
{
public:
    using Loader = ResourceLoader<T>;

    /// @param loader The loader should exists as long as this.
    explicit ResourceCache(Loader& loader = {})
        : m_loader(loader)
    {
    }

    virtual ~ResourceCache() = default;

    /// Get a resource from an id, or load it if it was not already loaded.
    T& operator()(const std::string& id)
    {
        if (m_cache.contains(id))
        {
            // returns if already loaded

            return m_cache.at(id);
        }
        else
        {
            // not here, loads the resource

            T& ret = m_cache[id]; // operator[] insert by with default-constructor.
            m_loader.loadResource(ret, id); // initialize the resource
            return ret;
        }
    }

private:
    /// @brief All already loaded assets.
    std::unordered_map<std::string, T> m_cache;

    /// @brief Loader functor.
    Loader& m_loader;
};
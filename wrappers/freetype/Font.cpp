#include "Font.hpp"
#include "private/FontImpl.hpp"

Font::Font()
    : m_impl(std::make_unique<FontImpl>())
{
}

// We still need to implement the destructor in .cpp because the destruction can't happen in header, the FontImpl is incomplete
Font::~Font() = default;

void Font::load(const std::filesystem::path& fontPath, int characterSize)
{
    return m_impl->load(fontPath, characterSize);
}

SDL_version Font::getFreeTypeCompiledVersion()
{
    return FontImpl::getFreeTypeCompiledVersion();
}

SDL_version Font::getFreeTypeLinkedVersion() const
{
    return m_impl->getFreeTypeLinkedVersion();
}

const Glyph& Font::getGlyph(char c) const
{
    // Note: the function is marked const, but it load the glyph if it does not exists yet
    // As we use pImpl/pointers, we don't need to use const_cast...
    return m_impl->getGlyph(c);
}

float Font::getLineHeight() const
{
    return m_impl->getLineHeight();
}

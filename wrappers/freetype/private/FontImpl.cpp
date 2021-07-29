#include "FontImpl.hpp"
#include <wrappers/gl/GL.hpp>
#include <wrappers/SDL.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

#define FT_Check(call) do { int error = (call); if(error) { throw FTException(error, #call " failed"); } } while(0)

FontImpl::FontImpl() noexcept(false)
{
}

FontImpl::~FontImpl() noexcept(false)
{
    reset();
}

void FontImpl::reset()
{
    if(m_face)
    {
        FT_Check(FT_Done_Face(m_face)); // Before closing freetype
        m_face = nullptr;
    }

    if(m_ft)
    {
        FT_Check(FT_Done_FreeType(m_ft));
        m_ft = nullptr;
    }

    m_lineHeight = 0.0f;
    m_chars.clear();
}

void FontImpl::load(const std::filesystem::path& fontPath, int characterSize)
{
    reset();

    std::cout << "Loading font " << fontPath << std::endl;

    FT_Check(FT_Init_FreeType(&m_ft));

    const char* path = fontPath.c_str();
    FT_Check(FT_New_Face(m_ft, path, 0, &m_face));
    FT_Check(FT_Set_Pixel_Sizes(m_face, 0, characterSize));

    //m_lineHeight = static_cast<float>(characterSize);

    // https://stackoverflow.com/questions/26486642/whats-the-proper-way-of-getting-text-bounding-box-in-freetype-2
    // 26.6 format: 1 unit = 1/64 pixel
    m_lineHeight = m_face->size->metrics.height / 64.0f;
}

SDL_version FontImpl::getFreeTypeCompiledVersion()
{
    SDL_version ret;
    ret.major = FREETYPE_MAJOR;
    ret.minor = FREETYPE_MINOR;
    ret.patch = FREETYPE_PATCH;

    return ret;
}

SDL_version FontImpl::getFreeTypeLinkedVersion() const
{
    FT_Int major, minor, patch;
    FT_Library_Version(m_ft, &major, &minor, &patch);

    SDL_version ret;
    ret.major = major;
    ret.minor = minor;
    ret.patch = patch;

    return ret;
}

const Glyph& FontImpl::getGlyph(char c)
{
    if(!m_chars.contains(c))
    {
        // The final character that will be loaded for later use
        Glyph glyph;

        const int bits = 8;

        // FT_LOAD_RENDER: pre-render the glyph in greyscale 8-bits => so we know a pixel is uint8 in range [0;255] luminance.
        FT_Check(FT_Load_Char(m_face, c, FT_LOAD_RENDER));

        // pitch = number of bytes for each row, pixels are always row major
        // however, the flow of the image (Y origin) can be top or down.
        // if pitch > 0, the 'flow' is to down, origin=up => We need to reverse Y
        // if pitch < 0, the 'flow' is to up, origin=down => How OpenGL treats texture (Textures origin is bottom-left corner)

        FT_Bitmap& bitmap = m_face->glyph->bitmap;

        if(bitmap.pitch > 0)
        {
            // Not ok, need to reverse the texture

            reverseBitmap(bitmap);
        }

        glyph.texture.bind();

        // disable byte-alignment restriction
        // texture should be multiple of 4 by default, but glyphs are greyscale so it could be of any size (= multiple of 1)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);

        // Texture generic options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glyph.size = {bitmap.width, bitmap.rows};

        glyph.bearing.x = m_face->glyph->bitmap_left;
        glyph.bearing.y = m_face->glyph->bitmap_top;

        // The FT_Glyph advance is in 1/64 pixel but Glyph advance is in pixel
        glyph.advance = static_cast<float>(m_face->glyph->advance.x) / 64.0f;

        m_chars.emplace(std::make_pair(c, std::move(glyph)));
    }

    return m_chars.at(c);
}

void FontImpl::reverseBitmap(FT_Bitmap& bitmap)
{
    std::vector<unsigned char> rowBuffer(bitmap.pitch); // Temporary buffer to store the row

    for(int row = 0; row < bitmap.rows / 2; ++row)
    {
        // Flip each row
        // rows / 2 round to lower, so if there is a odd number of row the center row will not be swapped
        // which is ok because it do not need to

        unsigned char *row1 = bitmap.buffer + bitmap.pitch * row;
        unsigned char *row2 = bitmap.buffer + bitmap.pitch * (bitmap.rows - 1 - row);

        std::swap_ranges(row1, row1 + bitmap.pitch, row2);
    }
}

float FontImpl::getLineHeight() const
{
    return m_lineHeight;
}

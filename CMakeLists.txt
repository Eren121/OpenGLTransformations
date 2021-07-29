cmake_minimum_required(VERSION 3.11)
project(OpenGLTransformations)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
include_directories(.)

include_directories("thirdparty/imgui/")
include_directories("thirdparty/imgui/backends")
set(SRC
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_demo.cpp
    thirdparty/imgui/imgui_draw.cpp
    thirdparty/imgui/imgui_tables.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/backends/imgui_impl_opengl3.cpp
    thirdparty/imgui/backends/imgui_impl_sdl.cpp

    main.cpp
    wrappers/SDL.cpp
    wrappers/SDL.hpp
    wrappers/nostd/source_location.hpp
    wrappers/nostd/source_location.cpp
    wrappers/gl/Shader.cpp
    wrappers/gl/Shader.hpp

    media/Window.cpp
    media/Window.hpp
    media/ResourceCache.hpp
    media/input/UnifiedInput.cpp
    media/input/UnifiedInput.hpp

    utility/Exception.cpp
    utility/Exception.hpp
    utility/Str.cpp
    utility/Str.hpp
    utility/IO.cpp
    utility/IO.hpp
    utility/math.cpp
    utility/math.hpp
    utility/Rect.hpp
    utility/Guard.hpp
    utility/offset_of.hpp

    utility/time/Clock.cpp
    utility/time/Clock.hpp
    utility/time/Time.cpp
    utility/time/Time.hpp
    utility/list_iterator.hpp

    wrappers/gl/Sprite.cpp
    wrappers/gl/Sprite.hpp
    wrappers/gl/VertexArray.cpp
    wrappers/gl/VertexArray.hpp
    wrappers/gl/Texture.cpp
    wrappers/gl/Texture.hpp
    wrappers/gl/RenderStates.hpp
    wrappers/gl/Line.cpp
    wrappers/gl/Line.hpp
    wrappers/gl/Transformable.cpp
    wrappers/gl/Transformable.hpp
    wrappers/gl/GL.cpp
    wrappers/gl/GL.hpp
    wrappers/gl/Circle.cpp
    wrappers/gl/Circle.hpp

    wrappers/freetype/Font.cpp
    wrappers/freetype/Font.hpp
    wrappers/freetype/Text.cpp
    wrappers/freetype/Text.hpp
    wrappers/freetype/FTException.cpp
    wrappers/freetype/FTException.hpp
    wrappers/freetype/private/FontImpl.cpp
    wrappers/freetype/private/FontImpl.hpp
    wrappers/freetype/Glyph.cpp
    wrappers/freetype/Glyph.hpp
    wrappers/freetype/RichText.cpp
    wrappers/freetype/RichText.hpp

    utility/time/FPSCounter.cpp
    utility/time/FPSCounter.hpp

    test/TestTransformable.hpp
    test/TestTransformable.cpp

    wrappers/gl/Shape.cpp
    wrappers/gl/Shape.hpp
    wrappers/gl/Vertex.hpp
    wrappers/gl/Vertex.cpp
    wrappers/gl/ConvexShape.cpp
    wrappers/gl/ConvexShape.hpp)


add_executable(OpenGLTransformations ${SRC})

#######################################

FetchContent_Declare(
        sigslot
        GIT_REPOSITORY https://github.com/palacaze/sigslot.git
        GIT_TAG 19a6f0f5ea11fc121fe67f81fd5e491f2d7a4637)
FetchContent_MakeAvailable(sigslot)
target_link_libraries(OpenGLTransformations PRIVATE Pal::Sigslot)

#######################################

FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG		   VER-2-11-0
)

FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
    FetchContent_Populate(freetype)
    add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()
target_link_libraries(OpenGLTransformations PRIVATE freetype)

#######################################

target_link_libraries(OpenGLTransformations PRIVATE SDL2 SDL2_image GL GLEW)
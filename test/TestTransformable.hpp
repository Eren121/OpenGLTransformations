#include "media/Window.hpp"
#include <wrappers/gl/RenderStates.hpp>
#include <wrappers/gl/Shape.hpp>
#include <wrappers/gl/ConvexShape.hpp>
#include <wrappers/gl/Circle.hpp>
#include <wrappers/freetype/Text.hpp>

/// @brief Test transformable with a IMGUI interface
class TestTransformable
{
public:
    TestTransformable();

    void run();

protected:
    void draw();

    void drawGrid(RenderStates states);

private:
    Window m_window;
    Shader m_shader;

    float m_zoom{3.0f};
    float m_gridRadius{10.0f};

    glm::vec2 m_origin{0.0f};
    glm::vec4 m_position{0.0f};
    glm::vec2 m_scale{1.0f};
    float m_rotation{0.0f};

    glm::vec4 m_outlineColor{1.0f};
    glm::vec4 m_fillColor{1.0f};
    float m_outlineThickness{0.02f};

    ConvexShape m_triangle;
    Circle m_circle;
    Text m_text;
    Drawable *m_current{&m_triangle};

    Font m_font;

    char m_string[100];

    bool m_noOutline{false};

    Vertex m_triangleVertices[3];
};
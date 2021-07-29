#include "TestTransformable.hpp"
#include <wrappers/gl/VertexArray.hpp>
#include <wrappers/gl/ConvexShape.hpp>
#include <wrappers/gl/Line.hpp>
#include <utility/math.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <glm/gtc/matrix_transform.hpp>

TestTransformable::TestTransformable()
    : m_window("Test transformable", 800, 800)
{
    std::filesystem::path path = std::filesystem::current_path() / "../assets";

    m_shader.load(path / "vert.glsl", path / "frag.glsl");
    m_font.load(path / "fonts/monofonto.ttf", 64);

    m_current = &m_triangle;

    char buf[] {"Loremp ipsum"};

    strcpy(m_string, buf);
    m_text.setString(m_string);
    m_text.setFont(&m_font);

    m_triangleVertices[0] = {{1, 0}, {1, 0, 0, 1}};
    m_triangleVertices[1] = {{0, 1}, {0, 1, 0, 1}};
    m_triangleVertices[2] = {{-1, 0}, {0, 0, 1, 1}};
}

void TestTransformable::draw()
{
    glm::mat4 view = glm::ortho(-m_zoom, m_zoom, -m_zoom, m_zoom);
    view *= glm::scale(view, {m_window.getSize().y / m_window.getSize().x, 1.0f, 1.0f}); // Aspect ratio

    RenderStates states;
    states.view = view;
    states.shader = &m_shader;

    if(auto *tr = dynamic_cast<Transformable*>(m_current))
    {
        tr->setOrigin(m_origin);
        tr->setPosition(m_position);
        tr->setRotation(m_rotation);
        tr->setScale(m_scale);
    }

    if(auto *shape = dynamic_cast<Shape*>(m_current))
    {
        shape->setOutlineColor(m_outlineColor);
        shape->setOutlineThickness(m_noOutline ? 0.0f : m_outlineThickness);
        shape->setColor(m_fillColor);
    }

    if(auto *txt = dynamic_cast<Text*>(m_current))
    {
        txt->setColor(m_fillColor);

        txt->setScale(txt->getScale() / txt->getFont()->getLineHeight());
        txt->setString(m_string);
    }

    if(m_current == &m_triangle)
    {
        m_triangle.setVerticesCount(3);
        for (int i = 0; i < 3; ++i)
        {
            m_triangle.setVertex(i, m_triangleVertices[i]);
        }
    }

    drawGrid(states);
    m_current->draw(states);

    if(m_current == &m_text)
    {
        Sprite sprite;
        sprite.setScale({m_text.getSize() / m_text.getFont()->getLineHeight()});
        sprite.setOrigin({-0.5f,  -0.5f}); // Same origin as the Font
        sprite.setColor({0, 1, 0, 0.5});
        sprite.draw(states);
    }

    ImGui::SliderFloat("Zoom", &m_zoom, 0.1f, 6.0f);

    if(ImGui::Button("Reset"))
    {
    }

    {
        if(ImGui::Selectable("Triangle", m_current == &m_triangle))
        {
            m_current = &m_triangle;
        }
        if(ImGui::Selectable("Circle", m_current == &m_circle))
        {
            m_current = &m_circle;
        }
        if(ImGui::Selectable("Text", m_current == &m_text))
        {
            m_current = &m_text;
        }
    }

    if(ImGui::CollapsingHeader("Transformation"))
    {
        ImGui::SliderFloat2("Origin", &m_origin.x, -2.0f, 2.0f);
        ImGui::SliderFloat2("Translation", &m_position.x, -2.0f, 2.0f);
        ImGui::SliderFloat("Rotation", &m_rotation, 0.0f, 2.0f * PI);
        ImGui::SliderFloat2("Scale", &m_scale.x, -2.0f, 2.0f);
    }

    if(ImGui::CollapsingHeader("Fill"))
    {
        ImGui::ColorPicker4("Fill color, ", &m_fillColor.r, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar);
    }

    if(ImGui::CollapsingHeader("Outline"))
    {
        ImGui::SliderFloat("Outline thickness", &m_outlineThickness, -2.0f, 2.0f);
        ImGui::ColorPicker4("Outline color, ", &m_outlineColor.r, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar);

        ImGui::Checkbox("Disable outline", &m_noOutline);
    }

    if(ImGui::CollapsingHeader("Triangle"))
    {
        for(int i = 0; i < 3; ++i)
        {
            std::ostringstream label;
            label << "Vertex " << static_cast<char>('A' + i);

            ImGui::SliderFloat2(label.str().c_str(), &m_triangleVertices[i].pos.x, -2.0f, 2.0f);
        }
    }
    if(ImGui::CollapsingHeader("Text"))
    {
        ImGui::Text("Text size : %fx%fpx", m_text.getSize().x, m_text.getSize().y);

        ImGui::InputText("String", m_string, sizeof(m_string));
    }
}

void TestTransformable::run()
{
    // https://decovar.dev/blog/2019/05/26/sdl-imgui/#sdl

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui_ImplSDL2_InitForOpenGL(m_window.getHandle(), nullptr);

    sigslot::scoped_connection conn = m_window.onEvent.connect([](const SDL_Event& event) {
        ImGui_ImplSDL2_ProcessEvent(&event);
    });

    while(m_window.isOpen())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_window.handleEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window.display();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    exit(0);
}

void TestTransformable::drawGrid(RenderStates states)
{
    Line line;
    glm::vec2 a, b;

    const int count = 10;

    // color
    glm::vec4 axis{1, 0, 0, 1}, noaxis{1};

    for(int x = -count; x <= count; ++x)
    {
        a = {x, -count};
        b = {x, count};

        line.update(a, b, x == 0 ? axis : noaxis);
        line.draw(states);
    }

    for(int y = -count; y <= count; ++y)
    {
        a = {-count, y};
        b = {count, y};
        line.update(a, b, y == 0 ? axis : noaxis);
        line.draw(states);
    }
}

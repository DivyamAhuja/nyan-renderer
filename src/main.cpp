#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

int main(int argc, char **argv)
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(1280, 720, "gl window", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to Initialize GLAD." << '\n';
    }

    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    bool show_another_window = true;
    ImVec4 clear_color(0.45f, 0.55f, 0.60f, 1.00f);

    GLfloat vertices[] =
        {
            -0.50f, -0.50f,  0.00f,  1.00f,  0.00f,  0.00f,  0.00f,  0.00f,     // Lower Left
            -0.50f,  0.50f,  0.00f,  0.00f,  1.00f,  0.00f,  0.00f,  1.00f,     // Top Left
             0.50f,  0.50f,  0.00f,  0.00f,  0.00f,  1.00f,  1.00f,  1.00f,     // Top Right
             0.50f, -0.50f,  0.00f,  1.00f,  1.00f,  1.00f,  1.00f,  0.00f,     // Bottom Right
        };

    // Indices for vertices order
    GLuint indices[] =
        {
            0, 2, 1,        // Left Triangle
            0, 3, 2,        // Right Triangle
        };

    VertexArray vao;
    vao.bind();
    VertexBuffer vbo(vertices, sizeof(vertices));
    ElementBuffer ebo(indices, sizeof(indices));
    
    VertexLayout layout;
    layout.push({.type = VertexLayout::element_type::FLOAT, .count = 3, .normalize = GL_FALSE, .name = "positions"});
    layout.push({.type = VertexLayout::element_type::FLOAT, .count = 3, .normalize = GL_FALSE, .name = "colors"});
    layout.push({.type = VertexLayout::element_type::FLOAT, .count = 2, .normalize = GL_FALSE, .name = "uv_coordinates"});
    vao.linkLayout(vbo, layout);
    
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    std::filesystem::path vertex_shader_path("res");
    vertex_shader_path /= "shaders";
    vertex_shader_path /= "default.vert";

    std::filesystem::path fragment_shader_path("res");
    fragment_shader_path /= "shaders";
    fragment_shader_path /= "default.frag";
    
    Shader def_shader(vertex_shader_path.c_str(), fragment_shader_path.c_str());

    Texture tex(
        std::filesystem::path("res").append("textures").append("nyan.png").c_str(),
        GL_TEXTURE_2D,
        GL_TEXTURE0,
        GL_RGBA,
        GL_UNSIGNED_BYTE
    );

    tex.texUnit(def_shader, "tex0", 0);

    GLuint uniID = glGetUniformLocation(def_shader.ID, "scale");
    
    float t = 0;
    float dt = 0.025;
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_another_window) {
            ImGui::Begin("Settings", &show_another_window);
            ImGui::Text("Helllooo");
            ImGui::End();
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        def_shader.Activate();
        glUniform1f(uniID, t);
        
        tex.bind();
        vao.bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        t += dt;
        if ( t >= 0.5 || t <= -0.5) dt *= -1;
        glfwSwapBuffers(window);
    }

    def_shader.Delete();
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    tex.Delete();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

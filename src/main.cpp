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
#include "Camera.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Model.h"

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
    std::filesystem::path executable_path = std::filesystem::path(argv[0]).parent_path();


    

    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(MessageCallback, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    bool show_info_window = true;
    ImVec4 clear_color(0.45f, 0.55f, 0.60f, 1.00f);

    std::vector<Vertex> vertices =
        std::vector<Vertex>({
            Vertex(100.0f * glm::vec3(-0.50f, -0.50f,  1.00f), glm::vec3(0.0f), glm::vec4(1.0f ,0.0f ,0.0f ,1.0f), glm::vec2(0.00f,  0.00f)),
            Vertex(100.0f * glm::vec3(-0.50f,  0.50f,  1.00f), glm::vec3(0.0f), glm::vec4(0.0f ,1.0f ,0.0f ,1.0f), glm::vec2(0.00f,  1.00f)),
            Vertex(100.0f * glm::vec3( 0.50f,  0.50f,  1.00f), glm::vec3(0.0f), glm::vec4(0.0f ,0.0f ,1.0f ,1.0f), glm::vec2(1.00f,  1.00f)),
            Vertex(100.0f * glm::vec3( 0.50f, -0.50f,  1.00f), glm::vec3(0.0f), glm::vec4(1.0f ,1.0f ,1.0f ,1.0f), glm::vec2(1.00f,  0.00f))
        });

    std::vector<GLuint> indices =
        std::vector<GLuint>({
            0, 2, 1,
            0, 3, 2,
        });

    std::vector<Texture> textures({
        Texture(
            std::filesystem::path(executable_path)
                .append("res")
                .append("textures")
                .append("nyan.png")
                .string().c_str(),
            "diffuse",
            (GLuint)0)
        });

    Mesh rect(vertices, indices, textures);


    std::filesystem::path vertex_shader_path = std::filesystem::path(executable_path)/"res"/"shaders"/"default.vert";
    std::filesystem::path fragment_shader_path = std::filesystem::path(executable_path)/"res"/"shaders"/"default.frag";
    
    Shader def_shader(vertex_shader_path.string().c_str(), fragment_shader_path.string().c_str());

    
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	def_shader.Activate();
	glUniform4f(glGetUniformLocation(def_shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(def_shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    std::filesystem::path modelPath;
    if (argc == 2 )
        modelPath = std::filesystem::path(argv[1]);
    else
        modelPath = std::filesystem::path(executable_path)/"res"/"models"/"sword"/"scene.gltf";    
    Model model(modelPath.string().c_str());

    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 100.0f));

    glfwSwapInterval(1);
    std::string FPS;
    double prevTime = 0, currTime = 0, timeDiff;
    unsigned int counter = 0;
    while (!glfwWindowShouldClose(window))
    {
        currTime = glfwGetTime();
        timeDiff = currTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0) {
            FPS = std::to_string((1.0 / timeDiff) * counter);
            prevTime = currTime;
            counter = 0;
        }
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_info_window) {
            ImGui::Begin("Info");
            ImGui::SetWindowSize(ImVec2(350.0f, 250.0f), ImGuiCond_Once);
            ImGui::SetWindowPos(ImVec2(20.0f, 10.0f), ImGuiCond_Once);
            ImGui::Text("FPS : %s", FPS.c_str());
            ImGui::Text("Camera:");
            ImGui::Text("  - Position: %f %f %f", camera.Position.x, camera.Position.y, camera.Position.z);
            ImGui::Text("  - Orientation: %f %f %f", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
            ImGui::Text("  - Up: %f %f %f", camera.Up.x, camera.Up.y, camera.Up.z);
            ImGui::End();
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(!io.WantCaptureKeyboard)
            camera.KeyboardInputs(window);
        if(!io.WantCaptureMouse)
            camera.MouseInputs(window);
        camera.updateMatrix(45.0f, 0.1f, 10000.0f);

        rect.draw(def_shader, camera);
        model.draw(def_shader, camera);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    def_shader.Delete();
    rect.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

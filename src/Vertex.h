#ifndef VERTEX_CLASS_H
#define VERTEX_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "VertexLayout.h"
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 texUV;
    glm::vec4 tangent;

    Vertex(
        glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 normal = glm::vec3(0.0f),
        glm::vec4 color = glm::vec4(1.0f),
        glm::vec2 texUV = glm::vec3(0.0f),
        glm::vec4 tangent = glm::vec4(0.0f)
    );

    static VertexLayout defaultVertexLayout();
};



#endif
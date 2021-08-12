#include "Vertex.h"

Vertex::Vertex(
    glm::vec3 position,
    glm::vec3 normal,
    glm::vec4 color,
    glm::vec2 texUV,
    glm::vec4 tangent)
    : position(position), normal(normal), color(color), texUV(texUV), tangent(tangent)
{
}

VertexLayout Vertex::defaultVertexLayout() {
    VertexLayout layout;
    layout.push({VertexLayout::element_type::FLOAT, 3, GL_FALSE, "position"});
    layout.push({VertexLayout::element_type::FLOAT, 3, GL_FALSE, "normal"});
    layout.push({VertexLayout::element_type::FLOAT, 4, GL_FALSE, "color"});
    layout.push({VertexLayout::element_type::FLOAT, 2, GL_FALSE, "texUV"});
    layout.push({VertexLayout::element_type::FLOAT, 4, GL_FALSE, "tangent"});
    return layout;
}
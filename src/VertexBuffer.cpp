#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices) {    
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete() {
    if (ID) {
        this->unbind();
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}

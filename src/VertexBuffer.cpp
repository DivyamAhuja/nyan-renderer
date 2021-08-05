#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) {    
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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

VertexBuffer::~VertexBuffer() {
    this->Delete();
}
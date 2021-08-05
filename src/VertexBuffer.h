#ifndef VERTEX_BUFFER_OBJECT_CLASS_H
#define VERTEX_BUFFER_OBJECT_CLASS_H

#include <glad/glad.h>

class VertexBuffer {

private:

public:
    GLuint ID;
    VertexBuffer(GLfloat* vertices, GLsizeiptr size);
    ~VertexBuffer();

    void bind();
    void unbind();
    void Delete();
};

#endif
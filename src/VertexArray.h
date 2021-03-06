#ifndef VERTEX_ARRAY_OBJECT_CLASS_H
#define VERTEX_ARRAY_OBJECT_CLASS_H

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexLayout.h"

class VertexArray {

public:
    GLuint ID;
    VertexArray();
    
    void linkAttrib(VertexBuffer& VBO, GLuint layout, GLuint count, GLboolean normalize, GLenum type, GLsizei stride, void* offset);
    void linkAttrib(GLuint layout, GLuint count, GLboolean normalize, GLenum type, GLsizei stride, void* offset);
    void linkLayout(VertexBuffer& VBO, VertexLayout& layout);
    void linkLayout(VertexLayout& layout);

    void bind();
    void unbind();
    void Delete();
};

#endif
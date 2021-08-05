#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
    this->Delete();
}

void VertexArray::linkAttrib(VertexBuffer& VBO, GLuint layout, GLuint count, GLboolean normalize, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.bind();
    glVertexAttribPointer(layout, count, type, normalize, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
};

void VertexArray::linkAttrib(GLuint layout, GLuint count, GLboolean normalize, GLenum type, GLsizeiptr stride, void* offset)
{
    glVertexAttribPointer(layout, count, type, normalize, stride, offset);
    glEnableVertexAttribArray(layout);
};

void VertexArray::linkLayout(VertexBuffer& VBO, VertexLayout& layout) {
    VBO.bind();
    this->linkLayout(layout);
    VBO.unbind();
}

void VertexArray::linkLayout(VertexLayout& layout) {
    GLuint i = 0;
    GLsizeiptr stride = layout.calculateStride();
    void* offset = (void*) 0;
    for(auto it = layout.getLayout().begin(); it != layout.getLayout().end(); it++) {
        this->linkAttrib(i, it->count, it->normalize, (GLenum)it->type, stride, offset);
        i++;
        offset = (void*)((GLbyte*)offset + (it->count * VertexLayout::sizeOfElementType(it->type)));
    }
}

void VertexArray::bind()
{
    glBindVertexArray(ID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::Delete()
{
    if (ID) {
        this->unbind();
        glDeleteVertexArrays(1, &ID);
        ID = 0;
    }
}
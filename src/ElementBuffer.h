#ifndef ELEMENT_BUFFER_OBJECT_CLASS_H
#define ELEMENT_BUFFER_OBJECT_CLASS_H

#include <glad/glad.h>

class ElementBuffer {

private:

public:
    GLuint ID;
    
    ElementBuffer(GLuint* indices, GLsizeiptr size);
    ~ElementBuffer();

    void bind();
    void unbind();
    void Delete();
};

#endif
#ifndef ELEMENT_BUFFER_OBJECT_CLASS_H
#define ELEMENT_BUFFER_OBJECT_CLASS_H

#include <glad/glad.h>
#include <vector>

class ElementBuffer {

private:

public:
    GLuint ID;
    
    ElementBuffer(std::vector<GLuint>& indices);
    
    void bind();
    void unbind();
    void Delete();
};

#endif
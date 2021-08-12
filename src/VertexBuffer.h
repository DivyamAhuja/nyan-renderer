#ifndef VERTEX_BUFFER_OBJECT_CLASS_H
#define VERTEX_BUFFER_OBJECT_CLASS_H

#include <glad/glad.h>
#include "Vertex.h"

class VertexBuffer {

private:

public:
    GLuint ID;
    VertexBuffer(std::vector<Vertex>& vertices);
    
    void bind();
    void unbind();
    void Delete();
};

#endif
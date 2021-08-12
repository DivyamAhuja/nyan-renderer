#ifndef VERTEX_LAYOUT_CLASS_H
#define VERTEX_LAYOUT_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <string>

class VertexLayout {
private:
    
public:
    enum class element_type {
        BYTE = GL_BYTE,
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        SHORT = GL_SHORT,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        INT = GL_INT,
        UNSIGNED_INT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT
    };
    
    struct layout_element{
        element_type type;
        GLuint count;
        GLboolean normalize = GL_FALSE;
        std::string name = ""; // Just in case... Not Necessary
    };

    std::vector<layout_element> layout;
    
    VertexLayout();
    
    std::vector<layout_element>& getLayout();
    
    void push(layout_element element);
    void pop();
    layout_element& peek();
    const GLsizei calculateStride();

    static GLsizei sizeOfElementType(element_type t);
};

#endif
#include "VertexLayout.h"

VertexLayout::VertexLayout()
    : layout(std::vector<layout_element>()) {

}

VertexLayout::~VertexLayout() {

}

std::vector<VertexLayout::layout_element>& VertexLayout::getLayout() {
    return layout;
}


void VertexLayout::push(layout_element element) {
    layout.push_back(element);

}

VertexLayout::layout_element& VertexLayout::peek() {
    return layout.back();
}

void VertexLayout::pop() {
    layout.pop_back();
}

const GLsizei VertexLayout::calculateStride() {
    GLsizei st = 0;
    for (auto it = layout.begin(); it != layout.end(); it++) {
        st += it->count * sizeOfElementType(it->type);
    }
    return st;
}

GLsizei VertexLayout::sizeOfElementType(element_type t) {
    switch (t)
    {
    case VertexLayout::element_type::BYTE :
        return sizeof(GLbyte);
    case VertexLayout::element_type::UNSIGNED_BYTE :
        return sizeof(GLubyte);
    case VertexLayout::element_type::SHORT :
        return sizeof(GLshort);
    case VertexLayout::element_type::UNSIGNED_SHORT :
        return sizeof(GLushort);
    case VertexLayout::element_type::INT :
        return sizeof(GLint);
    case VertexLayout::element_type::UNSIGNED_INT :
        return sizeof(GLuint);
    case VertexLayout::element_type::FLOAT :
        return sizeof(GLfloat);
    default:
        return 0;
    }
    return 0;
}
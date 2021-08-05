#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "Shader.h"

class Texture {
private:

public:
    GLuint ID;
    GLenum type;
    int imgWidth, imgHeight, numColorChannels;
    
    Texture() = delete;
    Texture(const char* filename, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    ~Texture();

    void texUnit(Shader& shader, const char* uniform, GLuint unit);

    void bind();
    void unbind();
    void Delete();
};

#endif